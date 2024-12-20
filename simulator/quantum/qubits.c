#include "qubits.h"
#include "qubits_cuda.h"
#define SMART_DEALLOCATION
#include "smart_allocation/smart_allocation.h"

#include <stdlib.h>
#include <math.h>

extern unsigned short cuda_enabled;

quantum_state *quantum_state_create(const unsigned int basis, const unsigned int size) {
    if(basis >= size) return NULL;

    quantum_state *temp = matrix_create_empty(size, 1);
    INDEX(temp, basis, 0) = complex_create(1, 0);
    return temp;
}

qubit *qubit_create() {
    qubit *temp = vector_create();
    INDEX(temp, 0, 0) = complex_create(1, 0);
    return temp;
}
qubit *qubit_create_init(const struct complex a0, const struct complex a1) {
    qubit *temp = vector_create_init(a0, a1);
    return temp;
}

qm_result *qm_result_create(const quantum_state * const state, const unsigned int value) {
    qm_result *temp = (qm_result *)smart_allocate(1, sizeof(qm_result));
    temp->state = (quantum_state *)state;
    B(temp, temp->state)
    temp->value = value;
    return temp;
}

qm_result *quantum_state_measure(const quantum_state * const q) {
    if(!q) return NULL;

    if(q->rows == q->columns) return quantum_state_measure_density_matrix(q);

    if(cuda_enabled) {
        return quantum_state_measure_cuda(q);
    }

    float random_value = (float)rand() / RAND_MAX;
    float current_state_probabilty = 0;
    qm_result *result = NULL;
    for(unsigned int i = 0; i < q->rows; i++) {
        current_state_probabilty += pow(complex_get_absolute(INDEX(q, i, 0)), 2);
        if(random_value < current_state_probabilty) {
            quantum_state *state = quantum_state_create(i, q->rows);
            result = qm_result_create(state, i);
            break;
        }
    }
    return result;
}
qm_result *quantum_state_measure_density_matrix(const quantum_operator * const d) {
    if(!d) return NULL;

    if(cuda_enabled) {
        return quantum_state_measure_density_matrix_cuda(d);
    }

    float random_value = (float)rand() / RAND_MAX;
    float current_state_probabilty = 0;
    qm_result *result = NULL;
    for(unsigned int i = 0; i < d->rows; i++) {
        // Here we get the probabilty by the expression: Tr(|i><i|d)
        // which is equal to the element on the diagonal of the density matrix
        // at the i-th row and i-th column.
        current_state_probabilty += INDEX(d, i, i).real;
        if(random_value < current_state_probabilty) {
            quantum_state *basis = quantum_state_create(i, d->rows);
            result = qm_result_create(basis, i);
            break;
        }
    }
    return result;
}
qm_result *quantum_state_measure_subsystem(const quantum_state * const q, 
                                                const unsigned int start_system_index, 
                                                const unsigned int end_system_index) 
{
    if(!q) return NULL;

    if(cuda_enabled) {
        return quantum_state_measure_subsystem_cuda(q, start_system_index, end_system_index);
    }

S
    #ifdef QUBITS_SHOW_SUBSYSTEM_MEASUREMENT
    printf("Measuring subsystem: start - %u, end - %u \n", 
        start_system_index, end_system_index);
    #endif

    quantum_operator *density_matrix = NULL;
    if(q->rows == q->columns) density_matrix = (quantum_operator *)q;
    else density_matrix = matrix_mul(
        q,
        vector_get_dual(q)
    );
    /*
    quantum_operator *r_density_matrix = matrix_get_partial_trace(
        density_matrix, 
        systems - (system_index + 1),
        systems
    );
    */

    const unsigned int systems = log2(q->rows);
    #ifdef QUBITS_SHOW_SUBSYSTEM_MEASUREMENT
    printf("Systems: %u \n", systems);
    #endif
    float random_value = (float)rand() / RAND_MAX;
    float current_state_probabilty = 0;
    qm_result *result = NULL;
    #ifdef QUBITS_SHOW_SUBSYSTEM_MEASUREMENT
    printf("Random value: %f \n", random_value);
    #endif

    const unsigned int preceding_qubits_count = start_system_index;
    const unsigned int measured_qubits_count = 
        (end_system_index - start_system_index) + 1;
    const unsigned int proceeding_qubits_count = 
        systems - (end_system_index + 1);

    #ifdef QUBITS_SHOW_SUBSYSTEM_MEASUREMENT
    printf("Measured qubits: %u \n", measured_qubits_count);
    #endif

    const unsigned int possible_outputs = pow(2, measured_qubits_count);
    for(unsigned int i = 0; i < possible_outputs; i++) {
        S
        quantum_operator *projector = NULL;
        if(preceding_qubits_count) projector = quantum_gate_create(
                                                pow(2, preceding_qubits_count));

        // Creating the orthogonal projector used to measure the exact qubits.
        quantum_state *basis = quantum_state_create(i, possible_outputs);
        quantum_state *basis_matrix = matrix_mul(basis, vector_get_dual(basis));
        if(projector == NULL) projector = basis_matrix;
        else projector = matrix_tensor_product(projector, basis_matrix);

        if(proceeding_qubits_count) 
            projector = matrix_tensor_product(projector, 
                                                quantum_gate_create(
                                                    pow(2, proceeding_qubits_count)));

        quantum_operator *applied_projector = matrix_mul(
            projector, 
            matrix_mul(
                density_matrix, 
                // Here we don't need to get the adjoint 
                // of the projector because it is Hermitian.
                projector
            )
        );

        current_state_probabilty += matrix_get_trace(applied_projector).real;

        // Combined result state of the system after measuremnt:
        float applied_projector_trace = matrix_get_trace(applied_projector).real;
        if(applied_projector_trace == 0) applied_projector_trace = 1;
        quantum_operator *result_state = matrix_mul_scalar(
            complex_create(1 / applied_projector_trace, 0), 
            applied_projector
        );

        #ifdef QUBITS_SHOW_SUBSYSTEM_MEASUREMENT
        printf("Current state probability: %f \n", current_state_probabilty);
        #endif
        if(random_value < current_state_probabilty) {
            result = qm_result_create(result_state, i);
            P(result)
            E
            break;
        }
        E
    }
P(result)
E
    if(result == NULL)
        printf("Error measuring subsystem: non-valid quantum state provided\n");
    return result;
}