#ifndef QUBITS_H
#define QUBITS_H

#include "../linear_algebra/linear_algebra.h"
#include "operators.h"

typedef vector quantum_state;
typedef quantum_state qubit;

// qm_result -> quantum_measurement_result
typedef struct {
    quantum_state *state;
    unsigned int value;
} qm_result;
typedef qm_result quantum_measurement_result;

quantum_state *quantum_state_create(const unsigned int basis, const unsigned int size);

qubit *qubit_create();
qubit *qubit_create_init(const struct complex a0, const struct complex a1);

qm_result *qm_result_create(const quantum_state * const state, const unsigned int value);

qm_result *quantum_state_measure(const quantum_state * const q);
qm_result *quantum_state_measure_density_matrix(const quantum_operator * const d);
qm_result *quantum_state_measure_subsystem(const quantum_state * const q, 
                                                const unsigned int system_index, 
                                                const unsigned int systems);

#endif