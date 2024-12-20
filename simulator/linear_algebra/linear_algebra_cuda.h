#ifndef LINEAR_ALGEBRA_CUDA_H
#define LINEAR_ALGEBRA_CUDA_H

// Uncomment to enable the logs:
// #define LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
// #define LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS_THOROUGH

#ifdef __cplusplus
extern "C" {
#endif

#include "linear_algebra.h"

#include "cuda_global.h"

enum operation {
    OPERATION_ADD,
    OPERATION_SUB,
    OPERATION_MUL,
    OPERATION_MUL_SCALAR
};

// The functions used for the CUDA implementation should be declared here

struct matrix *matrix_add_cuda(const struct matrix * const m1, 
                                    const struct matrix * const m2);
struct matrix *matrix_sub_cuda(const struct matrix * const m1, 
                                    const struct matrix * const m2);
struct matrix *matrix_mul_cuda(const struct matrix * const m1, 
                                    const struct matrix * const m2);
struct matrix *matrix_mul_scalar_cuda(const struct complex s, 
                                    const struct matrix * const m);

struct matrix *matrix_tensor_product_cuda(const struct matrix * const m1, 
                                            const struct matrix * const m2);

#ifdef __cplusplus
}
#endif

#endif