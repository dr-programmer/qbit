#ifndef SMART_ALLOCATION_H
#define SMART_ALLOCATION_H

#include <stdlib.h>

// Uncomment to enable the logs:
// #define SMART_ALLOCATION_SHOW_PTR_CREATION
// #define SMART_ALLOCATION_SHOW_SEARCH
// #define SMART_ALLOCATION_SHOW_PROMOTION
// #define SMART_ALLOCATION_SHOW_BINDING
// #define SMART_ALLOCATION_SHOW_END_FREE
// #define SMART_ALLOCATION_SHOW_ALLOCATION
// #define SMART_ALLOCATION_SHOW_SMART_FREE

#ifdef SMART_DEALLOCATION

void smart_allocation_stack_push();
void smart_allocation_stack_pop();
int smart_allocation_promote_ptr(const void * const ptr);
int smart_allocation_bind_ptr(const void * const par, const void * const child);
void smart_allocation_stack_clean();


#ifdef SMART_DEALLOCATION_EXPLICIT

#define START smart_allocation_stack_push();
#define END smart_allocation_stack_pop();
#define PROMOTE(PTR) smart_allocation_promote_ptr(PTR);
#define BIND(PAR, CHILD) smart_allocation_bind_ptr(PAR, CHILD);
#define CLEAN smart_allocation_stack_clean();

#else

#define S smart_allocation_stack_push();
#define E smart_allocation_stack_pop();
#define P(PTR) smart_allocation_promote_ptr(PTR);
#define B(PAR, CHILD) smart_allocation_bind_ptr(PAR, CHILD);
#define C smart_allocation_stack_clean();

#endif

#else

void smart_allocation_setup();
void smart_allocation_free();

#endif

void *smart_allocate(const unsigned int num, const size_t size);
int smart_free(const void * const ptr);

#endif