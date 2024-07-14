#include <stdlib.h>

#include "complex_numbers.h"

struct complex *complex_create_ptr(const float real, const float imaginary) {
    struct complex *temp = (struct complex *)calloc(1, sizeof(struct complex));
    temp->real = real;
    temp->imaginary = imaginary;
    return temp;
}
struct complex complex_create(const float real, const float imaginary) {
    struct complex temp = {
        .real = real, 
        .imaginary = imaginary
    };
    return temp;
}

struct complex *complex_get_conjugate_ptr(const struct complex * const num) {
    if(!num) return NULL;

    struct complex *temp = complex_create_ptr(num->real, -num->imaginary);
    return temp;
}
struct complex complex_get_conjugate(const struct complex * const num) {
    if(!num) return complex_create(0, 0);

    struct complex temp = complex_create(num->real, -num->imaginary);
    return temp;
}
void complex_change_to_conjugate(struct complex * const num) {
    if(!num) return;

    num->imaginary = -num->imaginary;
}