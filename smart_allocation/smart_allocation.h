#ifndef SMART_ALLOCATION_H
#define SMART_ALLOCATION_H

#include <stdlib.h>

#ifdef SMART_DEALLOCATION

void smart_allocation_stack_push();
void smart_allocation_stack_pop();
int smart_allocation_promote_ptr(const void * const ptr);

#ifdef SMART_DEALLOCATION_EXPLICIT

#define START smart_allocation_stack_push();
#define END smart_allocation_stack_pop();
#define PROMOTE(PTR) smart_allocation_promote_ptr(PTR);

#else

#define S smart_allocation_stack_push();
#define E smart_allocation_stack_pop();
#define P(PTR) smart_allocation_promote_ptr(PTR);

#endif

#else

void smart_allocation_setup();
void smart_allocation_free();

#endif

void *smart_allocate(const unsigned int num, const size_t size);
int smart_free(const void * const ptr);

#endif