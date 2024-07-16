#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

#include <stdio.h>

struct complex {
    float real;
    float imaginary;
};

struct complex *complex_create_ptr(const float real, const float imaginary);
struct complex complex_create(const float real, const float imaginary);

void complex_print(const struct complex * const num);

struct complex *complex_get_conjugate_ptr(const struct complex * const num);
struct complex complex_get_conjugate(const struct complex * const num);
void complex_change_to_conjugate(struct complex * const num);

float complex_get_absolute(const struct complex * const num);

struct complex complex_add(const struct complex * const num1, 
                                const struct complex * const num2);
struct complex complex_sub(const struct complex * const num1, 
                                const struct complex * const num2);
struct complex complex_mul(const struct complex * const num1, 
                                const struct complex * const num2);
struct complex complex_div(const struct complex * const num1, 
                                const struct complex * const num2);

#endif