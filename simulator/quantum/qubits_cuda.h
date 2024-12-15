#ifndef QUBITS_CUDA_H
#define QUBITS_CUDA_H

// Uncomment to enable the logs:
// #define QUBITS_CUDA_SHOW_OPERATIONS
// #define QUBITS_CUDA_SHOW_OPERATIONS_THOROUGH

#ifdef __cplusplus
extern "C" {
#endif

#include "qubits.h"

#include "cuda_global.h"

// The functions used for the CUDA implementation should be declared here

qm_result *quantum_state_measure_cuda(const quantum_state * const q);
qm_result *quantum_state_measure_density_matrix_cuda(const quantum_operator * const d);
qm_result *quantum_state_measure_subsystem_cuda(const quantum_state * const q, 
                                                const unsigned int start_system_index, 
                                                const unsigned int end_system_index);

#ifdef __cplusplus
}
#endif

#endif