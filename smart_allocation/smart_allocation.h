#ifndef SMART_ALLOCATION_H
#define SMART_ALLOCATION_H

#include <stdlib.h>

void smart_allocation_setup();

void *smart_allocate(const unsigned int num, const size_t size);

void smart_allocation_free();

#endif