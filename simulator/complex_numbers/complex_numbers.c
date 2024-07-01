#include <stdlib.h>

#include "complex_numbers.h"

struct complex *complex_create(const float real, const float imaginary) {
    struct complex *temp = (struct complex *)calloc(1, sizeof(struct complex));
    temp->real = real;
    temp->imaginary = imaginary;
    return temp;
}