#include <stdio.h>

#include "smart_allocation/smart_allocation.h"
#include "linear_algebra/linear_algebra.h"

int main() {
    smart_allocation_setup();

    vector *v1 = vector_create();
    v1->fields[0][0] = complex_create(1, 0);
    v1->fields[1][0] = complex_create(2, 0);
    matrix_print(v1);
    dual_vector *dv1 = vector_get_dual(v1);
    matrix_print(dv1);

    struct matrix *result = matrix_mul(v1, dv1);
    matrix_print(result);
    result = matrix_mul_scalar(complex_create(3, 3), result);
    matrix_print(result);

    struct complex inner_product = vector_inner_product(v1, v1);
    printf("\n");
    complex_print(inner_product);
    printf("\n");

    smart_allocation_free();
    return 0;
}