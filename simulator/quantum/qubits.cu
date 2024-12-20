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

    if(accumulated_probability + probability > random_value) {
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

    if(accumulated_probability + probability > random_value) {
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

__global__ void quantum_state_measure_subsystem_kernel(const struct complex * const state, 
                                            unsigned int * const result, 
                                            const size_t length, 
                                            const float random_value, 
                                            float * const current_state_probability, 
                                            int * const done, 
                                            const unsigned int measured_qubits_count, 
                                            const unsigned int preceding_qubits_count,  
                                            const unsigned int proceeding_qubits_count) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= length || atomicAdd(done, 0) == 1) return;

    /* 
    In a quantum system, the state of n qubits is represented as an index in binary, 
    where each bit corresponds to a qubit's state (0 or 1). For example, in a 3-qubit 
    system, the index '101' (binary) corresponds to the state |101>. To measure a 
    subset of qubits, we shift the index right by the number of proceeding qubits so 
    that the measured qubits are aligned to the least significant bits (the rightmost bits). 
    Then, a bitwise AND operation is applied with a mask that isolates the bits corresponding 
    to the measured qubits. The mask is generated by (1 << measured_qubits_count) - 1, 
    which creates a binary number with the least significant bits set to 1, matching 
    the number of measured qubits. This operation effectively extracts the group ID 
    corresponding to the measured qubits, ignoring the bits for the preceding and 
    proceeding qubits. 
    */
    unsigned int group_id = (index >> proceeding_qubits_count) 
                                & ((1 << measured_qubits_count) - 1);

    float magnitude_squared = state[index].real * state[index].real 
        + state[index].imaginary * state[index].imaginary;

    atomicAdd(&current_state_probability[group_id], magnitude_squared);

    __syncthreads(); // Ensure all threads finish probability computation

    #ifdef QUBITS_CUDA_SHOW_KERNEL_OPERATIONS
    printf("Index: %u\n", index);
    printf("Group ID: %u for index %u\n", group_id, index);
    printf("Magnitude squared: %f for index %u\n", magnitude_squared, index);
    printf("Probability: %f for group id %u\n", 
        current_state_probability[group_id], group_id);
    #endif

    if(index == 0) {
        float cumulative_probability = 0;
        const unsigned int possible_outputs = 1 << measured_qubits_count;
        for(unsigned int i = 0; i < possible_outputs; ++i) {
            cumulative_probability += current_state_probability[i];
            if(random_value < cumulative_probability) {
                atomicExch(result, i);
                atomicExch(done, 1);
                break;
            }
        }
    }
}

__global__ void quantum_state_collapse_to_subsystem_kernel(struct complex * const state, 
                                            const unsigned int result, 
                                            const size_t length, 
                                            const float * const current_state_probability, 
                                            const unsigned int measured_qubits_count, 
                                            const unsigned int preceding_qubits_count,  
                                            const unsigned int proceeding_qubits_count) 
{
    unsigned int index = blockIdx.x * blockDim.x + threadIdx.x;

    if(index >= length) return;

    // The explanation for the group ID calculation is the same as in the measurement kernel
    unsigned int group_id = (index >> proceeding_qubits_count) 
                                & ((1 << measured_qubits_count) - 1);

    // Zero out amplitudes not belonging to the measured group
    if(group_id != result) {
        state[index].real = 0;
        state[index].imaginary = 0;
    }
    else {
        // Normalize the remaining amplitudes
        float norm_factor = sqrtf(current_state_probability[result]);
        if(norm_factor > 0) {
            state[index].real /= norm_factor;
            state[index].imaginary /= norm_factor;
        }
    }
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

    const unsigned int possible_outputs = 1 << measured_qubits_count;

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Possible outputs: %u \n", possible_outputs);
    #endif

    size_t length_q = q->rows;
    size_t size_q = sizeof(struct complex) * length_q;

    struct complex *cuda_q;
    unsigned int *cuda_result;
    float *cuda_current_state_probability;
    int *cuda_done;
    CUDA_CHECK(cudaMalloc(&cuda_q, size_q));
    CUDA_CHECK(cudaMalloc(&cuda_result, sizeof(unsigned int)));
    CUDA_CHECK(cudaMalloc(&cuda_current_state_probability, possible_outputs * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&cuda_done, sizeof(int)));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Allocated\n");
    #endif

    CUDA_CHECK(cudaMemcpy(cuda_q, q->fields, size_q, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(cuda_result, 0, sizeof(unsigned int)));
    CUDA_CHECK(cudaMemset(cuda_current_state_probability, 0, 
                            possible_outputs * sizeof(float)));
    CUDA_CHECK(cudaMemset(cuda_done, 0, sizeof(int)));

    float random_value = (float)rand() / RAND_MAX;

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Random value: %f\n", random_value);
    #endif

    // Ensures the number of blocks is enough by rounding up
    int blocksPerGrid = (length_q + DTCPB - 1) / DTCPB;

    quantum_state_measure_subsystem_kernel<<<blocksPerGrid, DTCPB>>>(cuda_q, cuda_result, 
                        length_q, random_value, cuda_current_state_probability, 
                        cuda_done, measured_qubits_count, preceding_qubits_count, 
                        proceeding_qubits_count);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    unsigned int result;
    CUDA_CHECK(cudaMemcpy(&result, cuda_result, 
                            sizeof(unsigned int), cudaMemcpyDeviceToHost));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("Measured result: %u\n", result);
    #endif

    quantum_state_collapse_to_subsystem_kernel<<<blocksPerGrid, DTCPB>>>(cuda_q, 
                        result, length_q, cuda_current_state_probability, 
                        measured_qubits_count, preceding_qubits_count, 
                        proceeding_qubits_count);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS
    printf("After kernel\n");
    #endif

    quantum_state *result_state = quantum_state_create(0, length_q);
    CUDA_CHECK(cudaMemcpy(result_state->fields, cuda_q, size_q, cudaMemcpyDeviceToHost));

    #ifdef QUBITS_CUDA_SHOW_OPERATIONS_THOROUGH
    printf("Collapsed state:\n");
    matrix_print(result_state);
    #endif

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