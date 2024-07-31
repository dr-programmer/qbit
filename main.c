#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "smart_allocation/smart_allocation.h"
#include "linear_algebra/linear_algebra.h"
#include "qubits.h"
#include "operators.h"
#include "algorithms.h"

extern FILE *yyin;
extern int yyparse();

int main() {
    smart_allocation_setup();

    vector *v1 = vector_create();
    v1->fields[0][0] = complex_create(1, 0);
    v1->fields[1][0] = complex_create(2, 0);
    matrix_print(v1);
    dual_vector *dv1 = vector_get_dual(v1);
    matrix_print(dv1);

    struct matrix *result = matrix_mul(v1, dv1);
    matrix_print(result);
    result = matrix_mul_scalar(complex_create(3, 3), result);
    matrix_print(result);

    struct complex inner_product = vector_inner_product(v1, v1);
    printf("\n");
    complex_print(inner_product);
    printf("\n\n");

    struct matrix *tensor = matrix_tensor_product(v1, v1);
    matrix_print(tensor);
    printf("\n");

    tensor = vector_get_dual(tensor);
    matrix_print(tensor);
    printf("\n");

    srand(time(0));
    printf("Von Neumann measurement in the computational basis of |+>: \n");
    qubit *one = qubit_create_init(complex_create(1/sqrt(2), 0), 
            complex_create(1/sqrt(2), 0));
    qm_result *one_qm_result = quantum_state_measure(one);
    matrix_print(one_qm_result->state);
    printf("Classical bit form: %u \n\n", one_qm_result->value);

    printf("The Hadamard gate (H): \n");
    qubit *basis_0 = quantum_state_create(0, 2);
    qubit *basis_1 = quantum_state_create(1, 2);
    quantum_gate *hadamard = quantum_gate_create_hadamard();
    matrix_print(hadamard);

    printf("\nHadamard plus (|+>): \n");

    qubit *hadamard_plus = matrix_mul(
        hadamard, 
        basis_0
    );
    matrix_print(hadamard_plus);

    printf("\nHadamard minus (|->): \n");

    qubit *hadamard_minus = matrix_mul(
        hadamard, 
        basis_1
    );
    matrix_print(hadamard_minus);

    printf("\nDeutsch algorithm: %hd \n", algorithm_deutsch(quantum_gate_create_cnot()));

    smart_allocation_free();
    return 0;
}