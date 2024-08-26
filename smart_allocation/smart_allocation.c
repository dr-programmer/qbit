#define SMART_DEALLOCATION
#include "smart_allocation.h"

#include <stdio.h>

#define SMART_ALLOCATION_PTR_DEFAULT_NUM_CHILDREN 8
#define SMART_ALLOCATION_ARR_DEFAULT_CAPACITY 64

struct ptr {
    void *ptr;
    int size;
    int capacity;
    struct ptr **children;
};

struct smart_allocation_arr {
    size_t size;
    size_t capacity;
    struct ptr *ptr;
};

struct smart_allocation_stack {
    struct smart_allocation_arr *hash;
    struct smart_allocation_stack *next;
};

struct used_indices {
    int *indices;
    size_t size;
    size_t capacity;
    struct used_indices *next;
};

static struct smart_allocation_stack *allocated = NULL;
static struct used_indices *allocated_indices = NULL;

static struct smart_allocation_arr *saa_create() {
    struct smart_allocation_arr *temp = 
        (struct smart_allocation_arr *)calloc(1, sizeof(struct smart_allocation_arr));
    temp->capacity = SMART_ALLOCATION_ARR_DEFAULT_CAPACITY;
    temp->ptr = (struct ptr *)calloc(temp->capacity, sizeof(struct ptr));
    return temp;
}

static struct smart_allocation_stack *sas_create() {
    struct smart_allocation_stack *temp = 
        (struct smart_allocation_stack *)calloc(1, sizeof(struct smart_allocation_stack));
    temp->hash = saa_create();
    return temp;
}

static struct used_indices *ui_create() {
    struct used_indices *temp = (struct used_indices *)calloc(1, sizeof(struct used_indices));
    temp->capacity = SMART_ALLOCATION_ARR_DEFAULT_CAPACITY;
    temp->indices = (int *)calloc(temp->capacity, sizeof(int));
    return temp;
}

void smart_allocation_stack_push() {
    struct smart_allocation_stack *tempS = allocated;
    allocated = sas_create();
    allocated->next = tempS;

    struct used_indices *tempI = allocated_indices;
    allocated_indices = ui_create();
    allocated_indices->next = tempI;
}

static long smart_hash_function(const void * const ptr, const size_t hash_capacity) {
    if(!ptr) return -1;

    long x = (long)ptr;

    // This algorithm can be found here:
    // https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
    // Here the 64-bit version is used (based on splitmix64).
    x = (x ^ (x >> 30)) * (long)(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * (long)(0x94d049bb133111eb);
    x = x ^ (x >> 31);

    return x % hash_capacity;
}

static int smart_allocation_indices_add_ptr_index(const unsigned int index) {
    if(allocated_indices->size >= allocated_indices->capacity * ((float)2/3)) {
        allocated_indices->capacity *= 2;
        allocated_indices->indices = 
            (int *)realloc(allocated_indices->indices, 
                                allocated_indices->capacity * sizeof(int));
        if(allocated_indices->indices == NULL) return 0;
    }

    #ifdef SMART_ALLOCATION_SHOW_PTR_CREATION
    printf("Ptr indices structure size = %zu; capacity = %zu \nTo add index = %u \n", 
                allocated_indices->size, allocated_indices->capacity, index);
    #endif

    allocated_indices->indices[allocated_indices->size++] = index;
    return 1;
}

static int smart_allocation_arr_add_ptr(const void * const ptr) {
    if(allocated->hash->size >= allocated->hash->capacity * ((float)2/3)) {
        allocated->hash->capacity *= 2;
        allocated->hash->ptr = 
            (struct ptr *)realloc(allocated->hash->ptr, 
                                allocated->hash->capacity * sizeof(struct ptr));
        if(allocated->hash->ptr == NULL) return 0;
    }

    #ifdef SMART_ALLOCATION_SHOW_PTR_CREATION
    printf("Creating %p \n", ptr);
    #endif

    long index = smart_hash_function(ptr, allocated->hash->capacity);
    #ifdef SMART_ALLOCATION_SHOW_PTR_CREATION
    printf("Hash value ptr index = %ld \n", index);
    #endif
    if(index == -1) return 0;

    for(; allocated->hash->ptr[index].ptr != NULL; 
                    index = (index + 1) % allocated->hash->capacity);

    #ifdef SMART_ALLOCATION_SHOW_PTR_CREATION
    printf("End result ptr index = %ld \n", index);
    #endif

    struct ptr *s_ptr = &allocated->hash->ptr[index];
    s_ptr->ptr = (void *)ptr;
    s_ptr->size = 0;
    s_ptr->capacity = 0;
    s_ptr->children = NULL;
    smart_allocation_indices_add_ptr_index(index);

    allocated->hash->size++;
    return 1;
}

static long smart_allocation_get_ptr_index(const void * const ptr) {
    if(!ptr) return -1;

    #ifdef SMART_ALLOCATION_SHOW_SEARCH
    printf("Searching for %p \n", ptr);
    #endif

    long index = smart_hash_function(ptr, allocated->hash->capacity);
    #ifdef SMART_ALLOCATION_SHOW_SEARCH
    printf("Hash value ptr index = %ld \n", index);
    #endif

    for(long safety = 0; allocated->hash->ptr[index].ptr != ptr; 
                    index = (index + 1) % allocated->hash->capacity) 
    {
        if(safety >= allocated->hash->capacity) return -1;
        safety++;
    }

    #ifdef SMART_ALLOCATION_SHOW_SEARCH
    printf("End result ptr index = %ld \n", index);
    #endif

    return index;
}

int smart_allocation_promote_ptr(const void * const ptr) {
    if(!ptr || !allocated->next) return 0;

    #ifdef SMART_ALLOCATION_SHOW_PROMOTION
    printf("Promoting %p\n", ptr);
    #endif

    long index = smart_allocation_get_ptr_index(ptr);
    if(index == -1) return 0;

    allocated->hash->ptr[index].ptr = NULL;
    struct ptr *par_ptr = &allocated->hash->ptr[index];

    struct smart_allocation_stack *tempS = allocated;
    allocated = allocated->next;
    struct used_indices *tempI = allocated_indices;
    allocated_indices = allocated_indices->next;
    smart_allocation_arr_add_ptr(ptr);
    for(unsigned int i = 0; i < par_ptr->size; i++) {

        #ifdef SMART_ALLOCATION_SHOW_PROMOTION
        printf("Promoting children %d\n", par_ptr->size);
        #endif

        void *child = par_ptr->children[i]->ptr;
        allocated = tempS;
        allocated_indices = tempI;
        smart_allocation_promote_ptr(child);
        allocated = allocated->next;
        allocated_indices = allocated_indices->next;
        smart_allocation_bind_ptr(ptr, child);
    }
    allocated = tempS;
    allocated_indices = tempI;

    if(par_ptr->children) free(par_ptr->children);

    return 1;
}

static int smart_allocation_bind_child_to_par(const long par_index, const long child_index) {
    struct ptr *par_ptr = &allocated->hash->ptr[par_index];
    if(par_ptr->capacity == 0) {
        par_ptr->capacity = SMART_ALLOCATION_PTR_DEFAULT_NUM_CHILDREN;
        par_ptr->children = (struct ptr **)calloc(par_ptr->capacity, sizeof(struct ptr *));
        if(par_ptr->children == NULL) return 0;
    }
    else if(par_ptr->size >= par_ptr->capacity * ((float)2/3)) {
        par_ptr->capacity *= 2;
        par_ptr->children = 
            (struct ptr **)realloc(par_ptr->children, 
                                    par_ptr->capacity * sizeof(struct ptr *));
        if(par_ptr->children == NULL) return 0;
    }

    #ifdef SMART_ALLOCATION_SHOW_BINDING
    printf("Par: size = %d; capacity = %d; ptr = %p \n", 
                par_ptr->size, par_ptr->capacity, par_ptr->ptr);
    #endif

    struct ptr *child_ptr = &allocated->hash->ptr[child_index];

    #ifdef SMART_ALLOCATION_SHOW_BINDING
    printf("Child Ptr field = %p \n", child_ptr->ptr);
    #endif

    par_ptr->children[par_ptr->size++] = child_ptr;
    return 1;
}
int smart_allocation_bind_ptr(const void * const par, const void * const child) {
    if(!par || !child) return 0;

    #ifdef SMART_ALLOCATION_SHOW_BINDING
    printf("Binding %p to %p\n", child, par);
    #endif

    long par_index = smart_allocation_get_ptr_index(par);
    if(par_index == -1) return 0;
    long child_index = smart_allocation_get_ptr_index(child);
    if(child_index == -1) return 0;

    #ifdef SMART_ALLOCATION_SHOW_BINDING
    printf("Found ptr indices to bind: %ld to %ld\n", child_index, par_index);
    #endif

    return smart_allocation_bind_child_to_par(par_index, child_index);
}

static void smart_allocation_free_current_ptrs() {
    #ifdef SMART_ALLOCATION_SHOW_END_FREE
    printf("Freeing \n");
    #endif
    for(unsigned int i = 0; i < allocated_indices->size; i++) {
        void *temp = allocated->hash->ptr[allocated_indices->indices[i]].ptr;
        #ifdef SMART_ALLOCATION_SHOW_END_FREE
        printf("Attempt to free %p \n", temp);
        #endif
        if(temp != NULL) {
            #ifdef SMART_ALLOCATION_SHOW_END_FREE
            printf("To free %p \n", temp);
            #endif
            struct ptr *s_ptr = &allocated->hash->ptr[allocated_indices->indices[i]];
            if(s_ptr->children) {
                free(s_ptr->children);
                s_ptr->children = NULL;
            }
            free(temp);
            s_ptr->ptr = NULL;
        }
    }
    free(allocated->hash->ptr);
}

void smart_allocation_stack_pop() {
    smart_allocation_free_current_ptrs();

    free(allocated->hash);

    struct smart_allocation_stack *tempS = allocated;
    allocated = allocated->next;
    free(tempS);

    struct used_indices *tempI = allocated_indices;
    allocated_indices = allocated_indices->next;
    free(tempI->indices);
    free(tempI);
}

void smart_allocation_stack_clean() {
    while(allocated) {
        smart_allocation_stack_pop();
    }
}

// ↑ With SMART_DEALLOCATION
// ------------------------------------------------------------------------
// ↓ Without SMART_DEALLOCATION

void smart_allocation_setup() {
    smart_allocation_stack_push();
}

void smart_allocation_free() {
    smart_allocation_stack_pop();
}

// ------------------------------------------------------------------------
// ↓ Always defined

void *smart_allocate(const unsigned int num, const size_t size) {
    #ifdef SMART_ALLOCATION_SHOW_ALLOCATION
    printf("alloca \n");
    #endif

    void *ptr = calloc(num, size);
    smart_allocation_arr_add_ptr(ptr);

    #ifdef SMART_ALLOCATION_SHOW_ALLOCATION
    printf("give alloca %p\n", ptr);
    #endif

    return ptr;
}

static int smart_allocation_free_ptr_children(struct ptr *ptr) {
    if(!ptr || !ptr->children) return 1;

    #ifdef SMART_ALLOCATION_SHOW_SMART_FREE
    printf("Freeing children: size = %d; capacity = %d; ptr = %p \n", 
                                        ptr->size, ptr->capacity, ptr->ptr);
    #endif

    for(unsigned int i = 0; i < ptr->size; i++) {
        smart_allocation_free_ptr_children(ptr->children[i]);
        if(ptr->children[i] != NULL && ptr->children[i]->ptr != NULL) {
            free(ptr->children[i]->ptr);
            ptr->children[i]->ptr = NULL;
            ptr->children[i] = NULL;
        }
    }
    free(ptr->children);
    ptr->children = NULL;
    return 0;
}
int smart_free(const void * const ptr) {
    if(!ptr) return 0;

    int success = 0;

    #ifdef SMART_ALLOCATION_SHOW_SMART_FREE
    printf("Attempt to free %p \n", ptr);
    #endif

    struct smart_allocation_stack *original = allocated;
    for(; allocated != NULL; allocated = allocated->next) {
        long index = smart_allocation_get_ptr_index(ptr);
        if(index != -1) {

            #ifdef SMART_ALLOCATION_SHOW_SMART_FREE
            printf("To free %p \n", ptr);
            #endif

            struct ptr *s_ptr = &allocated->hash->ptr[index];
            if(!s_ptr) printf("NULL! \n");
            smart_allocation_free_ptr_children(s_ptr);
            free(s_ptr->ptr);
            s_ptr->ptr = NULL;
            success = 1;

            #ifdef SMART_ALLOCATION_SHOW_SMART_FREE
            printf("Freed %p\n", ptr);
            #endif

            break;
        }
    }
    allocated = original;

    return success;
}