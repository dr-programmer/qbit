#include "operators.h"

// I = the Identity matrix = [1 0
//                            0 1]

quantum_gate *quantum_gate_create(const unsigned int dimensions) {
    /* The result gate:
        1 0
        0 1
    */
    quantum_gate *temp = matrix_create(dimensions, dimensions);
    return temp;
}
quantum_gate *quantum_gate_create_pauli_x() {
    /* The result gate:
        0 1
        1 0
    */
    quantum_gate *temp = matrix_create_empty(2, 2);
    temp->fields[0][1] = complex_create(1, 0);
    temp->fields[1][0] = complex_create(1, 0);
    return temp;
}
quantum_gate *quantum_gate_create_pauli_y() {
    /* The result gate:
        0 -i
        i  0
    */
    quantum_gate *temp = matrix_create_empty(2, 2);
    temp->fields[0][1] = complex_create(0, -1);
    temp->fields[1][0] = complex_create(0, 1);
    return temp;
}
quantum_gate *quantum_gate_create_pauli_z() {
    /* The result gate:
        1  0
        0 -1
    */
    quantum_gate *temp = quantum_gate_create(2);
    temp->fields[1][1] = complex_create(-1, 0);
    return temp;
}

quantum_gate *quantum_gate_create_rotation_x(const float angle) {
    // The result gate:
    // e^((-i*angle*Pauli_X)/2) = cos(angle/2)*I - i*sin(angle/2)*Pauli_X
    quantum_gate *i = quantum_gate_create(2);
    quantum_gate *x = quantum_gate_create_pauli_x();
    i = matrix_mul_scalar(complex_create(cos(angle / 2), 0), i);
    x = matrix_mul_scalar(complex_create(0, -sin(angle / 2)), x);
    quantum_gate *result = matrix_add(i, x);
    return result;
}
quantum_gate *quantum_gate_create_rotation_y(const float angle) {
    // The result gate:
    // e^((-i*angle*Pauli_Y)/2) = cos(angle/2)*I - i*sin(angle/2)*Pauli_Y
    quantum_gate *i = quantum_gate_create(2);
    quantum_gate *y = quantum_gate_create_pauli_y();
    i = matrix_mul_scalar(complex_create(cos(angle / 2), 0), i);
    y = matrix_mul_scalar(complex_create(0, -sin(angle / 2)), y);
    quantum_gate *result = matrix_add(i, y);
    return result;
}
quantum_gate *quantum_gate_create_rotation_z(const float angle) {
    // The result gate:
    // e^((-i*angle*Pauli_Z)/2) = cos(angle/2)*I - i*sin(angle/2)*Pauli_Z
    quantum_gate *i = quantum_gate_create(2);
    quantum_gate *z = quantum_gate_create_pauli_z();
    i = matrix_mul_scalar(complex_create(cos(angle / 2), 0), i);
    z = matrix_mul_scalar(complex_create(0, -sin(angle / 2)), z);
    quantum_gate *result = matrix_add(i, z);
    return result;
}

quantum_gate *quantum_gate_create_hadamard() {
    /* The result gate:
        1/√2 * [1  1
                1 -1]        
    */
    quantum_gate *x = quantum_gate_create_pauli_x();
    quantum_gate *z = quantum_gate_create_pauli_z();
    quantum_gate *combined = matrix_add(x, z);
    combined = matrix_mul_scalar(complex_create(1/sqrt(2), 0), combined);
    return combined;
}
quantum_gate *quantum_gate_create_pi_eighths() {
    /* The result gate:
        1 0
        0 e^(i*pi/4)
    */
    quantum_gate *temp = quantum_gate_create(2);
    temp->fields[1][1] = complex_create(cos(C_PI / 4), sin(C_PI / 4));
    return temp;
}

quantum_gate *quantum_gate_create_controlled_1_qubit_gate(const quantum_gate * const u) {
    if(!u) return NULL;

    quantum_gate *i = quantum_gate_create(2);

    // The following is the operator |0><0|
    quantum_operator *basis_0 = matrix_create_empty(2, 2);
    basis_0->fields[0][0] = complex_create(1, 0);
    // The following is the operator |1><1|
    quantum_operator *basis_1 = matrix_create_empty(2, 2);
    basis_1->fields[1][1] = complex_create(1, 0);

    // The following is the expression |0><0|⊗I + |1><1|⊗U
    quantum_gate *result = matrix_add(
        matrix_tensor_product(basis_0, i), 
        matrix_tensor_product(basis_1, u)
    );
    return result;
}
quantum_gate *quantum_gate_create_cnot() {
    return quantum_gate_create_controlled_1_qubit_gate(quantum_gate_create_pauli_x());
}