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

struct complex complex_pow(struct complex num, struct complex pow) {
    // a + ib = pow

    // r = magnitude
    const float magnitude = complex_get_absolute(num);
    if(magnitude == 0) return complex_create(0, 0);
    #ifdef COMPLEX_SHOW_POW_CALCULATIONS
    printf("\nMagnitude: %f", magnitude);
    #endif

    // θ = angle
    float angle = atan2(num.imaginary / magnitude, num.real / magnitude);
    #ifdef COMPLEX_SHOW_POW_CALCULATIONS
    printf("\nAngle (rad): %f", angle);
    #endif

    // The full formula:
    // e^(a*ln(r)+ib*ln(r)+iθa-θb) = 
    // e^(a*ln(r)-θb)*e^(i*(θa+b*ln(r))) = 
    // e^(a*ln(r)-θb)*(cos(θa+b*ln(r)) + i*sin(θa+b*ln(r)))

    // The first factor (real):
    // e^(a*ln(r)-θb)
    struct complex real_factor = {0, 0};
    real_factor.real = exp(pow.real * log(magnitude) - angle * pow.imaginary);
    #ifdef COMPLEX_SHOW_POW_CALCULATIONS
    printf("\nReal factor: %f", real_factor.real);
    #endif

    // The second factor (complex):
    // e^(i*(θa+b*ln(r)))
    // which extends to:
    // cos(θa+b*ln(r)) + i*sin(θa+b*ln(r))
    struct complex complex_factor = {0, 0};
    float temp_power = angle * pow.real + pow.imaginary * log(magnitude);
    #ifdef COMPLEX_SHOW_POW_CALCULATIONS
    printf("\nTemp power: %f", temp_power);
    #endif
    complex_factor.real = cos(temp_power);
    complex_factor.imaginary = sin(temp_power);
    #ifdef COMPLEX_SHOW_POW_CALCULATIONS
    printf("\nComplex factor: (");
    complex_print(complex_factor);
    printf(")");
    #endif

    struct complex result = complex_mul(real_factor, complex_factor);
    return result;
}