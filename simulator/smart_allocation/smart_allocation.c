#include "smart_aloocation.h"

static struct smart_allocation_arr {
    size_t size;
    size_t capacity;
    void **ptr;
};

static struct smart_allocation_arr allocated;

void smart_allocation_setup() {
    allocated.size = 0;
    allocated.capacity = 2;
    allocated.ptr = (void **)calloc(allocated.capacity, sizeof(void *));
}

static int smart_allocation_arr_add_ptr(const void * const ptr) {
    if(allocated.size >= allocated.capacity) {
        allocated.capacity *= 2;
        allocated.ptr = (void **)realloc(allocated.capacity, sizeof(void));
        if(allocated.ptr == NULL) return 0;
    }

    allocated.ptr[allocated.size++] = ptr;
    return 1;
}
void *smart_allocate(const size_t size, const unsigned int num) {
    void *ptr = calloc(num, size);
    smart_allocation_arr_add_ptr(ptr);
    return ptr;
}

void smart_allocation_free() {
    for(size_t i = 0; i < allocated.size; i++) {
        free(allocated.ptr[i]);
    }
}