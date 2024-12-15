#include "linear_algebra_cuda.h"
extern "C" {
#define SMART_DEALLOCATION
#include "smart_allocation.h"
}

#include <stdio.h>

__global__ void matrix_add_kernel(const struct complex * const m1, 
                                    const struct complex * const m2, 
                                    struct complex * const result, 
                                    size_t length) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= length) return;

    result[index] = {m1[index].real + m2[index].real, 
                        m1[index].imaginary + m2[index].imaginary};
}
__global__ void matrix_sub_kernel(const struct complex * const m1, 
                                    const struct complex * const m2, 
                                    struct complex * const result, 
                                    size_t length) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index >= length) return;

    result[index] = {m1[index].real - m2[index].real, 
                        m1[index].imaginary - m2[index].imaginary};
}
__global__ void matrix_mul_kernel(const struct complex * const m1, 
                                    const struct complex * const m2, 
                                    struct complex * const result, 
                                    size_t rows, size_t columns, size_t shared_dim) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= rows * columns) return;

    unsigned int row = index / columns;
    unsigned int column = index % columns;

    struct complex sum = {0, 0};
    for(size_t i = 0; i < shared_dim; i++) {
        struct complex a = m1[row * shared_dim + i];
        struct complex b = m2[i * columns + column];
        sum.real += a.real * b.real - a.imaginary * b.imaginary;
        sum.imaginary += a.real * b.imaginary + a.imaginary * b.real;
    }

    result[row * columns + column] = sum;
}
__global__ void matrix_mul_scalar_kernel(const struct complex s, 
                                            const struct complex * const m, 
                                            struct complex * const result, 
                                            size_t length) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= length) return;

    result[index] = {s.real * m[index].real - s.imaginary * m[index].imaginary, 
                        s.real * m[index].imaginary + s.imaginary * m[index].real};
}

__global__ void print_array(struct complex *array, int size) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) {
        printf("array[%d] = %f + %fi\n", idx, array[idx].real, array[idx].imaginary);
    }
}
struct matrix *matrix_operation_cuda(const void *m1_s_void, 
                                        const void *m2_void, 
                                        const enum operation operation) 
{
    if(!m1_s_void || !m2_void) return NULL;

    const struct matrix *m1, *m2;
    struct complex s;

    if(operation == OPERATION_MUL_SCALAR) s = *(const struct complex *)m1_s_void;
    else m1 = (const struct matrix *)m1_s_void;
    m2 = (const struct matrix *)m2_void;

    switch(operation) {
        case OPERATION_ADD ... OPERATION_SUB:
            if(m1->rows != m2->rows || m1->columns != m2->columns) return NULL;
            break;
        case OPERATION_MUL:
            if(m1->columns != m2->rows) return NULL;
            break;
        case OPERATION_MUL_SCALAR:
            break;
        default:
            return NULL;
    }

    // length = the number of complex numbers in the matrix
    // size = the size of the matrix in bytes
    size_t length_m1 = 0;
    size_t size_m1 = 0;
    size_t length_m2 = m2->rows * m2->columns;
    size_t size_m2 = sizeof(struct complex) * length_m2;
    size_t length;
    size_t size;

    if(operation == OPERATION_MUL_SCALAR) {
        #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
        printf("Mul scalar\n");
        #endif
        length = length_m2;
        size = size_m2;
    }
    else if(operation == OPERATION_MUL) {
        #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
        printf("Mul\n");
        #endif
        length_m1 = m1->rows * m1->columns;
        size_m1 = sizeof(struct complex) * length_m1;

        length = m1->rows * m2->columns;
        size = sizeof(struct complex) * length;
    }
    else {
        #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
        printf("Add or sub\n");
        #endif
        length_m1 = m1->rows * m1->columns;
        size_m1 = sizeof(struct complex) * length_m1;

        length = length_m1;
        size = size_m1;
    }

    struct complex *cuda_m1, *cuda_m2, *cuda_result;
    if(operation != OPERATION_MUL_SCALAR) CUDA_CHECK(cudaMalloc(&cuda_m1, size_m1));
    CUDA_CHECK(cudaMalloc(&cuda_m2, size_m2));
    CUDA_CHECK(cudaMalloc(&cuda_result, size));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("Allocated\n");
    #endif

    if(operation != OPERATION_MUL_SCALAR) 
        CUDA_CHECK(cudaMemcpy(cuda_m1, m1->fields, size_m1, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(cuda_m2, m2->fields, size_m2, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(cuda_result, 0, size));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("To kernel\n");
    #endif

    // Ensures the number of blocks is enough by rounding up
    int blocksPerGrid = (length + DTCPB - 1) / DTCPB;
    if(operation == OPERATION_ADD) 
        matrix_add_kernel<<<blocksPerGrid, DTCPB>>>(cuda_m1, cuda_m2, cuda_result, length);
    else if(operation == OPERATION_SUB) 
        matrix_sub_kernel<<<blocksPerGrid, DTCPB>>>(cuda_m1, cuda_m2, cuda_result, length);
    else if(operation == OPERATION_MUL) 
        matrix_mul_kernel<<<blocksPerGrid, DTCPB>>>(cuda_m1, cuda_m2, cuda_result, 
                                                        m1->rows, m2->columns, m1->columns);
    else if(operation == OPERATION_MUL_SCALAR) 
        matrix_mul_scalar_kernel<<<blocksPerGrid, DTCPB>>>(s, cuda_m2, cuda_result, length);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("After kernel\n");
    #endif

    struct matrix *result;
    if(operation == OPERATION_MUL) result = matrix_create_empty(m1->rows, m2->columns);
    else result = matrix_create_empty(m2->rows, m2->columns);
    CUDA_CHECK(cudaMemcpy(result->fields, cuda_result, size, cudaMemcpyDeviceToHost));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS_THOROUGH
    printf("result:\n");
    matrix_print(result);
    printf("For:\n");
    operation != OPERATION_MUL_SCALAR ? matrix_print(m1) : complex_print(s);
    if(operation == OPERATION_MUL_SCALAR) printf("\n");
    printf("And:\n");
    matrix_print(m2);
    printf("M1\n");
    if(operation != OPERATION_MUL_SCALAR) 
        print_array<<<blocksPerGrid, DTCPB>>>(cuda_m1, length_m1);
    else {
        complex_print(s);
        printf("\n");
    }
    CUDA_CHECK(cudaDeviceSynchronize());
    printf("M2\n");
    print_array<<<blocksPerGrid, DTCPB>>>(cuda_m2, length_m2);
    CUDA_CHECK(cudaDeviceSynchronize());
    printf("Result\n");
    print_array<<<blocksPerGrid, DTCPB>>>(cuda_result, length);
    CUDA_CHECK(cudaDeviceSynchronize());
    printf("M1 length: %zu\n", length_m1);
    printf("M2 length: %zu\n", length_m2);
    #endif

    if(operation != OPERATION_MUL_SCALAR) CUDA_CHECK(cudaFree(cuda_m1));
    CUDA_CHECK(cudaFree(cuda_m2));
    CUDA_CHECK(cudaFree(cuda_result));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("Freed\n");
    #endif

    return result;
}
extern "C" struct matrix *matrix_add_cuda(const struct matrix * const m1, 
                                    const struct matrix * const m2) 
{
    return matrix_operation_cuda(m1, m2, OPERATION_ADD);
}
extern "C" struct matrix *matrix_sub_cuda(const struct matrix * const m1, 
                                    const struct matrix * const m2) 
{
    return matrix_operation_cuda(m1, m2, OPERATION_SUB);
}
extern "C" struct matrix *matrix_mul_cuda(const struct matrix * const m1, 
                                    const struct matrix * const m2) 
{
    return matrix_operation_cuda(m1, m2, OPERATION_MUL);
}
extern "C" struct matrix *matrix_mul_scalar_cuda(const struct complex s, 
                                    const struct matrix * const m) 
{
    return matrix_operation_cuda(&s, m, OPERATION_MUL_SCALAR);
}

__global__ void matrix_tensor_product_kernel(const struct complex * const m1, 
                                                const struct complex * const m2, 
                                                struct complex * const result, 
                                                size_t rows, size_t columns, 
                                                size_t m1_rows, size_t m1_columns, 
                                                size_t m2_rows, size_t m2_columns) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= rows * columns) return;

    unsigned int row = index / columns;
    unsigned int column = index % columns;

    struct complex a = m1[(row / m2_rows) * m1_columns + (column / m2_columns)];
    struct complex b = m2[(row % m2_rows) * m2_columns + (column % m2_columns)];

    result[row * columns + column] = {a.real * b.real - a.imaginary * b.imaginary, 
                                        a.real * b.imaginary + a.imaginary * b.real};
}

extern "C" struct matrix *matrix_tensor_product_cuda(const struct matrix * const m1, 
                                                        const struct matrix * const m2) 
{
    if(!m1 || !m2) return NULL;

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("Tensor product\n");
    #endif

    size_t rows = m1->rows * m2->rows;
    size_t columns = m1->columns * m2->columns;

    size_t length_m1 = m1->rows * m1->columns;
    size_t size_m1 = sizeof(struct complex) * length_m1;
    size_t length_m2 = m2->rows * m2->columns;
    size_t size_m2 = sizeof(struct complex) * length_m2;
    size_t length = length_m1 * length_m2;
    size_t size = sizeof(struct complex) * length;

    struct complex *cuda_m1, *cuda_m2, *cuda_result;
    CUDA_CHECK(cudaMalloc(&cuda_m1, size_m1));
    CUDA_CHECK(cudaMalloc(&cuda_m2, size_m2));
    CUDA_CHECK(cudaMalloc(&cuda_result, size));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("Allocated\n");
    #endif

    CUDA_CHECK(cudaMemcpy(cuda_m1, m1->fields, size_m1, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(cuda_m2, m2->fields, size_m2, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(cuda_result, 0, size));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("To kernel\n");
    #endif

    // Ensures the number of blocks is enough by rounding up
    int blocksPerGrid = (length + DTCPB - 1) / DTCPB;
    matrix_tensor_product_kernel<<<blocksPerGrid, DTCPB>>>(cuda_m1, cuda_m2, 
                                                                    cuda_result, 
                                                                    rows, columns, 
                                                                    m1->rows, m1->columns, 
                                                                    m2->rows, m2->columns);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("After kernel\n");
    #endif

    struct matrix *result = matrix_create_empty(rows, columns);
    CUDA_CHECK(cudaMemcpy(result->fields, cuda_result, size, cudaMemcpyDeviceToHost));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS_THOROUGH
    printf("result:\n");
    matrix_print(result);
    printf("For:\n");
    matrix_print(m1);
    printf("And:\n");
    matrix_print(m2);
    printf("M1\n");
    print_array<<<blocksPerGrid2D, threadsPerBlock2D>>>(cuda_m1, length_m1);
    CUDA_CHECK(cudaDeviceSynchronize());
    printf("M2\n");
    print_array<<<blocksPerGrid2D, threadsPerBlock2D>>>(cuda_m2, length_m2);
    CUDA_CHECK(cudaDeviceSynchronize());
    printf("Result\n");
    print_array<<<blocksPerGrid2D, threadsPerBlock2D>>>(cuda_result, length);
    CUDA_CHECK(cudaDeviceSynchronize());
    printf("M1 length: %zu\n", length_m1);
    printf("M2 length: %zu\n", length_m2);
    #endif

    CUDA_CHECK(cudaFree(cuda_m1));
    CUDA_CHECK(cudaFree(cuda_m2));
    CUDA_CHECK(cudaFree(cuda_result));

    #ifdef LINEAR_ALGEBRA_CUDA_SHOW_OPERATION_CALCULATIONS
    printf("Freed\n");
    #endif

    return result;
}