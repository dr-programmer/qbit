#include "smart_allocation.h"

#define SMART_ALLOCATION_ARR_DEFAULT_CAPACITY 128

struct smart_allocation_arr {
    size_t size;
    size_t capacity;
    void **ptr;
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
    temp->ptr = (void **)calloc(temp->capacity, sizeof(void *));
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
            (int *)realloc(allocated_indices, allocated_indices->capacity * sizeof(int));
        if(allocated_indices->indices == NULL) return 0;
    }

    allocated_indices->indices[allocated_indices->size++] = index;
    return 1;
}

static int smart_allocation_arr_add_ptr(const void * const ptr) {
    if(allocated->hash->size >= allocated->hash->capacity * ((float)2/3)) {
        allocated->hash->capacity *= 2;
        allocated->hash->ptr = 
            (void **)realloc(allocated->hash->ptr, 
                                allocated->hash->capacity * sizeof(void *));
        if(allocated->hash->ptr == NULL) return 0;
    }

    long index = smart_hash_function(ptr, allocated->hash->capacity);
    if(index = -1) return 0;

    for(; allocated->hash->ptr[index] != NULL; 
                    index = (index + 1) % allocated->hash->capacity);

    allocated->hash->ptr[index] = (void *)ptr;
    smart_allocation_indices_add_ptr_index(index);

    allocated->hash->size++;
    return 1;
}

int smart_allocation_promote_ptr(const void * const ptr) {
    if(!ptr || !allocated->next) return 0;

    long index = smart_hash_function(ptr, allocated->hash->capacity);

    for(long safety = 0; allocated->hash->ptr[index] != ptr; 
                    index = (index + 1) % allocated->hash->capacity) 
    {
        if(safety >= allocated->hash->capacity) return 0;
        safety++;
    }

    allocated->hash->ptr[index] = NULL;

    struct smart_allocation_stack *temp = allocated;
    allocated = allocated->next;
    smart_allocation_arr_add_ptr(ptr);
    allocated = temp;

    return 1;
}

static void smart_allocation_free_current_ptrs() {
    for(unsigned int i = 0; i < allocated_indices->size; i++) {
        void *temp = allocated->hash->ptr[allocated_indices->indices[i]];
        if(temp != NULL) free(temp);
    }
    free(allocated->hash->ptr);
}

void smart_allocation_stack_pop() {
    smart_allocation_free_current_ptrs();

    free(allocated->hash);

    struct smart_allocation_stack *temp = allocated;
    allocated = allocated->next;
    free(temp);
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

void *smart_allocate(const unsigned int num, const size_t size) {
    void *ptr = calloc(num, size);
    smart_allocation_arr_add_ptr(ptr);
    return ptr;
}