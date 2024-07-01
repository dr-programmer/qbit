#ifndef COMPLEX_NUMBERS_H
#define COMPLEX_NUMBERS_H

struct complex {
    float real;
    float imaginary;
};

struct complex *complex_create(const float real, const float imaginary);

#endif