#ifndef OPERATORS_H
#define OPERATORS_H

#include "../linear_algebra/linear_algebra.h"

#include <math.h>

#define C_PI (2 * asin(1.0))

typedef struct matrix quantum_operator;
typedef quantum_operator quantum_gate;

quantum_gate *quantum_gate_create(const unsigned int dimensions);
quantum_gate *quantum_gate_create_pauli_x();
quantum_gate *quantum_gate_create_pauli_y();
quantum_gate *quantum_gate_create_pauli_z();

// In the following functions and any other function that requires an angle 
// in this project the angle should be given in radians
// (unless specifically mentioned).

// The set of any two of the following three gates is a universal set for all 1-qubit gates
quantum_gate *quantum_gate_create_rotation_x(const float angle);
quantum_gate *quantum_gate_create_rotation_y(const float angle);
quantum_gate *quantum_gate_create_rotation_z(const float angle);

// The set of the following two gates is a universal set for all 1-qubit gates
quantum_gate *quantum_gate_create_hadamard();
quantum_gate *quantum_gate_create_pi_eighths();

quantum_gate *quantum_gate_create_controlled_1_qubit_gate(const quantum_gate * const u);
quantum_gate *quantum_gate_create_cnot();

#endif