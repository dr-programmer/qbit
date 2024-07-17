#include "complex_numbers.h"
#include "../smart_allocation/smart_allocation.h"

#include <math.h>

struct complex *complex_create_ptr(const float real, const float imaginary) {
    struct complex *temp = (struct complex *)smart_allocate(1, sizeof(struct complex));
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

void complex_print(struct complex num) {
    printf("%f + %fi", num.real, num.imaginary);
}

struct complex *complex_get_conjugate_ptr(const struct complex * const num) {
    if(!num) return NULL;

    struct complex *temp = complex_create_ptr(num->real, -num->imaginary);
    return temp;
}
struct complex complex_get_conjugate(struct complex num) {
    struct complex temp = complex_create(num.real, -num.imaginary);
    return temp;
}
void complex_change_to_conjugate(struct complex * const num) {
    if(!num) return;

    num->imaginary = -num->imaginary;
}

float complex_get_absolute(struct complex num) {
    return sqrt(num.real * num.real + num.imaginary * num.imaginary);
}

struct complex complex_add(struct complex num1, struct complex num2) 
{
    return complex_create(num1.real + num2.real, num1.imaginary + num2.imaginary);
}
struct complex complex_sub(struct complex num1, struct complex num2) 
{
    return complex_create(num1.real - num2.real, num1.imaginary - num2.imaginary);
}
struct complex complex_mul(struct complex num1, struct complex num2) 
{
    return complex_create(
        num1.real * num2.real - num1.imaginary * num2.imaginary, 
        num1.real * num2.imaginary + num1.imaginary * num2.real
    );
}
struct complex complex_div(struct complex num1, struct complex num2) 
{
    struct complex denominator_conjugate = complex_get_conjugate(num2);
    struct complex new_numerator = complex_mul(num1, denominator_conjugate);
    float real_denominator = num2.real * num2.real + num2.imaginary * num2.imaginary;
    // ^~~~> Here we don't need to call the complex_mul() to create a new 
    // complex denominator because when we multiple a complex number by its 
    // conjugate we get a real number. That's why I chose to use directly a real 
    // number (float) - for performance gains (one function call less).
    return complex_create(
        new_numerator.real / real_denominator, 
        new_numerator.imaginary / real_denominator
    );
}