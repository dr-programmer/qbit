#include "qubits_cuda.h"
extern "C" {
#define SMART_DEALLOCATION
#include "smart_allocation.h"
}

#include <stdio.h>
#include <stdlib.h>

__global__ void quantum_state_measure_kernel(const struct complex * const state, 
                                                unsigned int * const result,  
                                                const size_t length, 
                                                const float random_value, 
                                                float * const current_state_probability, 
                                                int * const done) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= length || atomicAdd(done, 0) == 1) return;

    float probability = state[index].real * state[index].real 
                        + state[index].imaginary * state[index].imaginary;
    float accumulated_probability = atomicAdd(current_state_probability, probability);

    if(accumulated_probability + probability >= random_value) {
        if(atomicExch(done, 1) == 0) {
            atomicExch(result, index);
        }
    }
}

extern "C" qm_result *quantum_state_measure_cuda(const quantum_state * const q) {
    if(!q) {
        fprintf(stderr, "Error: quantum_state_measure_cuda: quantum_state is NULL\n");
        return NULL;
    }

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("quantum_state_measure_cuda\n");
    #endif

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS_THOROUGH
    printf("Measuring state:\n");
    matrix_print(q);
    #endif

    size_t length = q->rows;
    size_t size = sizeof(struct complex) * length;

    struct complex *cuda_q;
    unsigned int *cuda_result;
    float *cuda_current_state_probability;
    int *cuda_done;
    CUDA_CHECK(cudaMalloc(&cuda_q, size));
    CUDA_CHECK(cudaMalloc(&cuda_result, sizeof(unsigned int)));
    CUDA_CHECK(cudaMalloc(&cuda_current_state_probability, sizeof(float)));
    CUDA_CHECK(cudaMalloc(&cuda_done, sizeof(int)));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Allocated\n");
    #endif

    CUDA_CHECK(cudaMemcpy(cuda_q, q->fields, size, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(cuda_result, 0, sizeof(unsigned int)));
    CUDA_CHECK(cudaMemset(cuda_current_state_probability, 0, sizeof(float)));
    CUDA_CHECK(cudaMemset(cuda_done, 0, sizeof(int)));

    float random_value = (float)rand() / RAND_MAX;

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("To kernel with random value: %f\n", random_value);
    #endif

    // Ensures the number of blocks is enough by rounding up
    int blocksPerGrid = (length + DTCPB - 1) / DTCPB;
    quantum_state_measure_kernel<<<blocksPerGrid, DTCPB>>>(cuda_q, cuda_result, 
                        length, random_value, cuda_current_state_probability, cuda_done);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("After kernel\n");
    #endif

    unsigned int result;
    CUDA_CHECK(cudaMemcpy(&result, cuda_result, 
                            sizeof(unsigned int), cudaMemcpyDeviceToHost));

    quantum_state *result_state = quantum_state_create(result, length);
    qm_result *qm_result = qm_result_create(result_state, result);

    CUDA_CHECK(cudaFree(cuda_q));
    CUDA_CHECK(cudaFree(cuda_result));
    CUDA_CHECK(cudaFree(cuda_current_state_probability));
    CUDA_CHECK(cudaFree(cuda_done));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Freed\n");
    #endif

    return qm_result;
}

__global__ void quantum_state_measure_density_matrix_kernel(
                                                const struct complex * const state, 
                                                unsigned int * const result,  
                                                const size_t length, 
                                                const float random_value, 
                                                float * const current_state_probability, 
                                                int * const done) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= length || atomicAdd(done, 0) == 1) return;

    unsigned int field_index = (index * length) + index;
    float probability = state[field_index].real;
    float accumulated_probability = atomicAdd(current_state_probability, probability);

    if(accumulated_probability + probability >= random_value) {
        if(atomicExch(done, 1) == 0) {
            atomicExch(result, index);
        }
    }
}

extern "C" qm_result *quantum_state_measure_density_matrix_cuda(
                                                const quantum_operator * const d) 
{
    if(!d) {
        fprintf(stderr, 
            "Error: quantum_state_measure_density_matrix_cuda: quantum_operator is NULL\n");
        return NULL;
    }

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("quantum_state_measure_density_matrix_cuda\n");
    #endif

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS_THOROUGH
    printf("Measuring density matrix:\n");
    matrix_print(d);
    #endif

    size_t length_m1 = d->rows * d->columns;
    size_t size_m1 = sizeof(struct complex) * length_m1;
    size_t length = d->rows;

    struct complex *cuda_d;
    unsigned int *cuda_result;
    float *cuda_current_state_probability;
    int *cuda_done;
    CUDA_CHECK(cudaMalloc(&cuda_d, size_m1));
    CUDA_CHECK(cudaMalloc(&cuda_result, sizeof(unsigned int)));
    CUDA_CHECK(cudaMalloc(&cuda_current_state_probability, sizeof(float)));
    CUDA_CHECK(cudaMalloc(&cuda_done, sizeof(int)));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Allocated\n");
    #endif

    CUDA_CHECK(cudaMemcpy(cuda_d, d->fields, size_m1, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(cuda_result, 0, sizeof(unsigned int)));
    CUDA_CHECK(cudaMemset(cuda_current_state_probability, 0, sizeof(float)));
    CUDA_CHECK(cudaMemset(cuda_done, 0, sizeof(int)));

    float random_value = (float)rand() / RAND_MAX;

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("To kernel with random value: %f\n", random_value);
    #endif

    // Ensures the number of blocks is enough by rounding up
    int blocksPerGrid = (length + DTCPB - 1) / DTCPB;
    quantum_state_measure_density_matrix_kernel<<<blocksPerGrid, DTCPB>>>(cuda_d, 
                                                cuda_result, length, random_value, 
                                                cuda_current_state_probability, cuda_done);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("After kernel\n");
    #endif

    unsigned int result;
    CUDA_CHECK(cudaMemcpy(&result, cuda_result, 
                            sizeof(unsigned int), cudaMemcpyDeviceToHost));

    quantum_state *result_state = quantum_state_create(result, length);
    qm_result *qm_result = qm_result_create(result_state, result);

    CUDA_CHECK(cudaFree(cuda_d));
    CUDA_CHECK(cudaFree(cuda_result));
    CUDA_CHECK(cudaFree(cuda_current_state_probability));
    CUDA_CHECK(cudaFree(cuda_done));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Freed\n");
    #endif

    return qm_result;
}

__global__ void quantum_state_measure_subsystem_kernel(...) 
{
    // To be implemented
}

extern "C" qm_result *quantum_state_measure_subsystem_cuda(const quantum_state * const q, 
                                                const unsigned int start_system_index, 
                                                const unsigned int end_system_index) 
{
    if(!q) {
        fprintf(stderr, 
            "Error: quantum_state_measure_subsystem_cuda: quantum_state is NULL\n");
        return NULL;
    }

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("quantum_state_measure_subsystem_cuda\n");
    #endif

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS_THOROUGH
    printf("Measuring subsystem:\n");
    matrix_print(q);
    #endif

    quantum_operator *density_matrix = NULL;
    if(q->rows == q->columns) density_matrix = (quantum_operator *)q;
    else density_matrix = matrix_mul(q, vector_get_dual(q));

    if(!density_matrix) {
        fprintf(stderr, 
            "Error: quantum_state_measure_subsystem_cuda: density matrix is NULL\n");
        return NULL;
    }

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS_THOROUGH
    printf("Density matrix:\n");
    matrix_print(d);
    #endif

    const unsigned int systems = log2(q->rows);

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Systems: %u \n", systems);
    #endif

    const unsigned int preceding_qubits_count = start_system_index;
    const unsigned int measured_qubits_count = 
        (end_system_index - start_system_index) + 1;
    const unsigned int proceeding_qubits_count = 
        systems - (end_system_index + 1);

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Measured qubits: %u \n", measured_qubits_count);
    #endif

    const unsigned int possible_outputs = pow(2, measured_qubits_count);

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Possible outputs: %u \n", possible_outputs);
    #endif

    size_t length_d = density_matrix->rows * density_matrix->columns;
    size_t size_d = sizeof(struct complex) * length_d;

    struct complex *cuda_d;
    unsigned int *cuda_result;
    float *cuda_current_state_probability;
    int *cuda_done;
    CUDA_CHECK(cudaMalloc(&cuda_d, size_d));
    CUDA_CHECK(cudaMalloc(&cuda_result, sizeof(unsigned int)));
    CUDA_CHECK(cudaMalloc(&cuda_current_state_probability, sizeof(float)));
    CUDA_CHECK(cudaMalloc(&cuda_done, sizeof(int)));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Allocated\n");
    #endif

    CUDA_CHECK(cudaMemcpy(cuda_d, density_matrix->fields, size_d, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(cuda_result, 0, sizeof(unsigned int)));
    CUDA_CHECK(cudaMemset(cuda_current_state_probability, 0, sizeof(float)));
    CUDA_CHECK(cudaMemset(cuda_done, 0, sizeof(int)));

    float random_value = (float)rand() / RAND_MAX;

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Random value: %f\n", random_value);
    #endif

    // Ensures the number of blocks is enough by rounding up
    int blocksPerGrid = (possible_outputs + DTCPB - 1) / DTCPB;
    quantum_state_measure_subsystem_kernel<<<blocksPerGrid, DTCPB>>>();
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("After kernel\n");
    #endif

    unsigned int result;
    CUDA_CHECK(cudaMemcpy(&result, cuda_result, 
                            sizeof(unsigned int), cudaMemcpyDeviceToHost));

    quantum_state *result_state = quantum_state_create(result, possible_outputs);

    qm_result *qm_result = qm_result_create(result_state, result);

    CUDA_CHECK(cudaFree(cuda_d));
    CUDA_CHECK(cudaFree(cuda_result));
    CUDA_CHECK(cudaFree(cuda_current_state_probability));
    CUDA_CHECK(cudaFree(cuda_done));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Freed\n");
    #endif

    return qm_result;
}