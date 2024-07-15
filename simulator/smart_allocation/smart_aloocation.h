#ifndef SMART_ALLOCATION_H
#define SMART_ALLOCATION_H

#include <stdlib.h>

void smart_allocation_setup();

void *smart_allocate(const size_t size, const unsigned int num);

void smart_allocation_free();

#endif