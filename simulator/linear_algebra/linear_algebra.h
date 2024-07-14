#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include "../complex_numbers/complex_numbers.h"

struct matrix {
    unsigned int rows;
    unsigned int columns;
    struct complex **fields;
};

struct matrix *matrix_create(const unsigned int rows, const unsigned int columns);

#endif