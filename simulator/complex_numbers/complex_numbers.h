#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

#include <stdio.h>

struct complex {
    float real;
    float imaginary;
};

struct complex *complex_create_ptr(const float real, const float imaginary);
struct complex complex_create(const float real, const float imaginary);

void complex_print(struct complex num);

struct complex *complex_get_conjugate_ptr(const struct complex * const num);
struct complex complex_get_conjugate(struct complex num);
void complex_change_to_conjugate(struct complex * const num);

float complex_get_absolute(struct complex num);

struct complex complex_add(struct complex num1, struct complex num2);
struct complex complex_sub(struct complex num1, struct complex num2);
struct complex complex_mul(struct complex num1, struct complex num2);
struct complex complex_div(struct complex num1, struct complex num2);

#endif