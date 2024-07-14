#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

struct complex {
    float real;
    float imaginary;
};

struct complex *complex_create_ptr(const float real, const float imaginary);
struct complex complex_create(const float real, const float imaginary);

struct complex *complex_get_conjugate_ptr(const struct complex * const num);
struct complex complex_get_conjugate(const struct complex * const num);
void complex_change_to_conjugate(struct complex * const num);

#endif