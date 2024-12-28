#include <stdio.h>
#include <math.h>
#include <time.h>
#define SMART_DEALLOCATION
#include "qbit.h"

int main() {S
srand(time(0));
cuda_enabled = 1;
struct matrix *t0 = matrix_create_empty(1, 1);
INDEX(t0, 0, 0) = complex_create(2.718280, 0.000000);
quantum_gate *e = t0;
struct matrix *t1 = matrix_create_empty(1, 1);
INDEX(t1, 0, 0) = complex_create(3.141590, 0.000000);
quantum_gate *pi = t1;
struct matrix *t2 = matrix_create_empty(1, 1);
INDEX(t2, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t3 = matrix_create_empty(1, 1);
INDEX(t3, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t4 = matrix_create_empty(1, 1);
INDEX(t4, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t5 = matrix_create_empty(1, 1);
INDEX(t5, 0, 0) = complex_create(1.000000, 0.000000);
quantum_gate *I = quantum_gate_create(2);
INDEX(I, 0, 0) = INDEX(t2, 0, 0);
INDEX(I, 0, 1) = INDEX(t3, 0, 0);
INDEX(I, 1, 0) = INDEX(t4, 0, 0);
INDEX(I, 1, 1) = INDEX(t5, 0, 0);
struct matrix *t6 = matrix_create_empty(1, 1);
INDEX(t6, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t7 = matrix_create_empty(1, 1);
INDEX(t7, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t8 = matrix_create_empty(1, 1);
INDEX(t8, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t9 = matrix_create_empty(1, 1);
INDEX(t9, 0, 0) = complex_create(0.000000, 0.000000);
quantum_gate *X = quantum_gate_create(2);
INDEX(X, 0, 0) = INDEX(t6, 0, 0);
INDEX(X, 0, 1) = INDEX(t7, 0, 0);
INDEX(X, 1, 0) = INDEX(t8, 0, 0);
INDEX(X, 1, 1) = INDEX(t9, 0, 0);
struct matrix *t10 = matrix_create_empty(1, 1);
INDEX(t10, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t11 = matrix_create_empty(1, 1);
INDEX(t11, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t11, 0, 0).real = sqrt(INDEX(t11, 0, 0).real);
struct matrix *t12 = matrix_create_empty(1, 1);
INDEX(t12, 0, 0).real = INDEX(t10, 0, 0).real / INDEX(t11, 0, 0).real;
struct matrix *t13 = matrix_create_empty(1, 1);
INDEX(t13, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t14 = matrix_create_empty(1, 1);
INDEX(t14, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t14, 0, 0).real = sqrt(INDEX(t14, 0, 0).real);
struct matrix *t15 = matrix_create_empty(1, 1);
INDEX(t15, 0, 0).real = INDEX(t13, 0, 0).real / INDEX(t14, 0, 0).real;
struct matrix *t16 = matrix_create_empty(1, 1);
INDEX(t16, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t17 = matrix_create_empty(1, 1);
INDEX(t17, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t17, 0, 0).real = sqrt(INDEX(t17, 0, 0).real);
struct matrix *t18 = matrix_create_empty(1, 1);
INDEX(t18, 0, 0).real = INDEX(t16, 0, 0).real / INDEX(t17, 0, 0).real;
struct matrix *t19 = matrix_create_empty(1, 1);
INDEX(t19, 0, 0) = complex_create(-1.000000, 0.000000);
struct matrix *t20 = matrix_create_empty(1, 1);
INDEX(t20, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t21 = matrix_create_empty(1, 1);
INDEX(t21, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t21, 0, 0).real = sqrt(INDEX(t21, 0, 0).real);
struct matrix *t22 = matrix_create_empty(1, 1);
INDEX(t22, 0, 0).real = INDEX(t20, 0, 0).real / INDEX(t21, 0, 0).real;
struct matrix *t23 = matrix_mul(t19, t22);
quantum_gate *H = quantum_gate_create(2);
INDEX(H, 0, 0) = INDEX(t12, 0, 0);
INDEX(H, 0, 1) = INDEX(t15, 0, 0);
INDEX(H, 1, 0) = INDEX(t18, 0, 0);
INDEX(H, 1, 1) = INDEX(t23, 0, 0);
qubit *t24 = quantum_state_create(0, 2);
qubit *t25 = quantum_state_create(0, 2);
quantum_state *t26 = vector_get_dual(t25);
struct matrix *t27 = matrix_mul(t24, t26);
struct matrix *t28 = matrix_tensor_product(t27, I);
qubit *t29 = quantum_state_create(1, 2);
qubit *t30 = quantum_state_create(1, 2);
quantum_state *t31 = vector_get_dual(t30);
struct matrix *t32 = matrix_mul(t29, t31);
struct matrix *t33 = matrix_tensor_product(t32, X);
struct matrix *t34 = matrix_add(t28, t33);
quantum_gate *CNOT = t34;
struct matrix *t35 = matrix_create_empty(1, 1);
INDEX(t35, 0, 0) = complex_create(6.000000, 0.000000);
quantum_gate *qubits_count = t35;
qubit *t36 = quantum_state_create(0, 2);
struct matrix *t37 = matrix_create_empty(1, 1);
INDEX(t37, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t38 = matrix_create_empty(1, 1);
INDEX(t38, 0, 0).real = INDEX(qubits_count, 0, 0).real / INDEX(t37, 0, 0).real;
struct matrix *t39 = matrix_tensor_product_n_times(t36, INDEX(t38, 0, 0).real);
qubit *t40 = quantum_state_create(1, 2);
struct matrix *t41 = matrix_create_empty(1, 1);
INDEX(t41, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t42 = matrix_create_empty(1, 1);
INDEX(t42, 0, 0).real = INDEX(qubits_count, 0, 0).real / INDEX(t41, 0, 0).real;
struct matrix *t43 = matrix_tensor_product_n_times(t40, INDEX(t42, 0, 0).real);
quantum_state *t44 = matrix_tensor_product(t39, t43);
struct matrix *t45 = matrix_tensor_product_n_times(H, INDEX(qubits_count, 0, 0).real);
quantum_state *t46 = matrix_mul(t45, t44);
if(t46->columns != 1) 
	t46 = matrix_mul(t46, matrix_get_adjoint(t45));
quantum_state *superposition = t46;
qm_result *t47 = quantum_state_measure(t46);
quantum_state *t48 = t47->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t47->value);
struct matrix *t49 = matrix_create_empty(1, 1);
INDEX(t49, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t50 = matrix_sub(qubits_count, t49);
struct matrix *t51 = matrix_tensor_product_n_times(I, INDEX(t50, 0, 0).real);
struct matrix *t52 = matrix_tensor_product(t51, I);
quantum_state *t53 = matrix_mul(t52, t48);
if(t53->columns != 1) 
	t53 = matrix_mul(t53, matrix_get_adjoint(t52));
struct matrix *t55 = matrix_create_empty(1, 1);
INDEX(t55, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t56 = matrix_create_empty(1, 1);
INDEX(t56, 0, 0) = complex_create(3.000000, 0.000000);
struct matrix *t57 = matrix_sub(qubits_count, t56);
qm_result *t54 = NULL;
{
const unsigned int start = INDEX(t55, 0, 0).real;
const unsigned int end = INDEX(t57, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t53->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t54 = quantum_state_measure(t53);
else t54 = quantum_state_measure_subsystem(t53, start, end);
}
quantum_state *t58 = t54->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t54->value);
struct matrix *t60 = matrix_create_empty(1, 1);
INDEX(t60, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t61 = matrix_create_empty(1, 1);
INDEX(t61, 0, 0) = complex_create(3.000000, 0.000000);
qm_result *t59 = NULL;
{
const unsigned int start = INDEX(t60, 0, 0).real;
const unsigned int end = INDEX(t61, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(superposition->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t59 = quantum_state_measure(superposition);
else t59 = quantum_state_measure_subsystem(superposition, start, end);
}
quantum_state *t62 = t59->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t59->value);
E
return 0;
}
