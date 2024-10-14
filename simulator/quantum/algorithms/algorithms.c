#include "algorithms.h"
#include "qubits.h"

short algorithm_deutsch(const quantum_gate * const gate) {
    if(!gate) return -1;
    if(gate->rows != 4 || gate->rows != gate->columns) return -1;

    // |0>
    qubit *register_0 = qubit_create();

    // H
    quantum_gate *hadamard = quantum_gate_create_hadamard();

    // |-> = H * |1>
    qubit *register_h_minus = matrix_mul(
        hadamard, 
        qubit_create_init(complex_create(0, 0), complex_create(1, 0))
    );

    register_0 = matrix_mul(
        hadamard, 
        register_0
    );
    quantum_state *combined = matrix_tensor_product(
        register_0, 
        register_h_minus
    );
    combined = matrix_mul(gate, combined);

    // The gate which applies a Hadamard gate only to the first qubit is U = H ⊗ I
    quantum_gate *hadamard_control_qubit = matrix_tensor_product(
        hadamard, 
        quantum_gate_create(2)
    );
    combined = matrix_mul(hadamard_control_qubit, combined);

    // A way of computing the result by measuring the whole system
    /*
    qm_result *result = quantum_state_measure(combined);
    printf("\nDeutch algorithm measurement result state: \n");
    matrix_print(result->state);
    if(result->value < 2) return 0;
    return 1;
    */

    // A way of computing the result by measuring only the first qubit
    qm_result *result = quantum_state_measure_subsystem(combined, 0, 0);
    printf("\nDeutch algorithm measurement result state: \n");
    matrix_print(result->state);
    return result->value;
}