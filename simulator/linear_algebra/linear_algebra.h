#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include "../complex_numbers/complex_numbers.h"

struct matrix {
    unsigned int rows;
    unsigned int columns;
    struct complex **fields;
};

typedef struct matrix vector;
typedef struct matrix dual_vector;

struct matrix *matrix_create(const unsigned int rows, const unsigned int columns);
struct matrix *matrix_create_empty(const unsigned int rows, const unsigned int columns);

void matrix_print(const struct matrix * const m);

struct matrix *matrix_add(const struct matrix * const m1, const struct matrix * const m2);
struct matrix *matrix_sub(const struct matrix * const m1, const struct matrix * const m2);
struct matrix *matrix_mul(const struct matrix * const m1, const struct matrix * const m2);
struct matrix *matrix_mul_scalar(const struct complex s, const struct matrix * const m);

struct matrix *matrix_tensor_product(const struct matrix * const m1, 
                                        const struct matrix * const m2);
struct matrix *matrix_tensor_product_n_times(const struct matrix * const m, 
                                                const unsigned int n);

struct matrix *matrix_transpose(const struct matrix * const m);

struct matrix *matrix_get_adjoint(const struct matrix * const m);

struct complex matrix_get_trace(const struct matrix * const m);
struct matrix *matrix_get_partial_trace(const struct matrix * const m, 
                                            const unsigned int space_index, 
                                            const unsigned int spaces);

vector *vector_create();
vector *vector_create_init(struct complex num1, struct complex num2);

dual_vector *vector_get_dual(vector const * const v);

struct complex vector_inner_product(const vector * const v1, const vector * const v2);

#endif