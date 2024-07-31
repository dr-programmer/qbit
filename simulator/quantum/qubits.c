#include "qubits.h"
#include "smart_allocation/smart_allocation.h"

#include <stdlib.h>
#include <math.h>

quantum_state *quantum_state_create(const unsigned int basis, const unsigned int size) {
    if(basis >= size) return NULL;

    quantum_state *temp = matrix_create_empty(size, 1);
    temp->fields[basis][0] = complex_create(1, 0);
    return temp;
}

qubit *qubit_create() {
    qubit *temp = vector_create();
    temp->fields[0][0] = complex_create(1, 0);
    return temp;
}
qubit *qubit_create_init(const struct complex a0, const struct complex a1) {
    qubit *temp = vector_create_init(a0, a1);
    return temp;
}

qm_result *qm_result_create(const quantum_state * const state, const unsigned int value) {
    qm_result *temp = (qm_result *)smart_allocate(1, sizeof(qm_result));
    temp->state = (quantum_state *)state;
    temp->value = value;
    return temp;
}

qm_result *quantum_state_measure(const quantum_state * const q) {
    if(!q) return NULL;

    float random_value = (float)rand() / RAND_MAX;
    float current_state_probabilty = 0;
    qm_result *result = NULL;
    for(unsigned int i = 0; i < q->rows; i++) {
        current_state_probabilty += pow(complex_get_absolute(q->fields[i][0]), 2);
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

    float random_value = (float)rand() / RAND_MAX;
    float current_state_probabilty = 0;
    qm_result *result = NULL;
    for(unsigned int i = 0; i < d->rows; i++) {
        // Here we get the probabilty by the expression: Tr(|i><i|d)
        quantum_state *basis = quantum_state_create(i, d->rows);
        quantum_operator *basis_matrix = matrix_mul(basis, vector_get_dual(basis));
        current_state_probabilty += matrix_get_trace(matrix_mul(basis_matrix, d)).real;
        if(random_value < current_state_probabilty) {
            result = qm_result_create(basis, i);
            break;
        }
    }
    return result;
}
qm_result *quantum_state_measure_subsystem(const quantum_state * const q, 
                                                const unsigned int system_index, 
                                                const unsigned int systems) 
{
    if(!q) return NULL;

    quantum_operator *density_matrix = matrix_mul(
        q,
        vector_get_dual(q)
    );
    quantum_operator *r_density_matrix = matrix_get_partial_trace(
        density_matrix, 
        systems - (system_index + 1),
        systems
    );
    return quantum_state_measure_density_matrix(r_density_matrix);
}