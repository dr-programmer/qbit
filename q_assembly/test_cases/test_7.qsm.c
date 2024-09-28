#include <stdio.h>
#include <math.h>
#include <time.h>
#define SMART_DEALLOCATION
#include "qbit.h"

int main() {S
srand(time(0));
struct matrix *t0 = matrix_create_empty(1, 1);
INDEX(t0, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t1 = matrix_create_empty(1, 1);
INDEX(t1, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t2 = matrix_create_empty(1, 1);
INDEX(t2, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t3 = matrix_create_empty(1, 1);
INDEX(t3, 0, 0) = complex_create(1.000000, 0.000000);
quantum_gate *I = quantum_gate_create(2);
INDEX(I, 0, 0) = INDEX(t0, 0, 0);
INDEX(I, 0, 1) = INDEX(t1, 0, 0);
INDEX(I, 1, 0) = INDEX(t2, 0, 0);
INDEX(I, 1, 1) = INDEX(t3, 0, 0);
struct matrix *t4 = matrix_create_empty(1, 1);
INDEX(t4, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t5 = matrix_create_empty(1, 1);
INDEX(t5, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t6 = matrix_create_empty(1, 1);
INDEX(t6, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t7 = matrix_create_empty(1, 1);
INDEX(t7, 0, 0) = complex_create(0.000000, 0.000000);
quantum_gate *X = quantum_gate_create(2);
INDEX(X, 0, 0) = INDEX(t4, 0, 0);
INDEX(X, 0, 1) = INDEX(t5, 0, 0);
INDEX(X, 1, 0) = INDEX(t6, 0, 0);
INDEX(X, 1, 1) = INDEX(t7, 0, 0);
struct matrix *t8 = matrix_create_empty(1, 1);
INDEX(t8, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t9 = matrix_create_empty(1, 1);
INDEX(t9, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t9, 0, 0).real = sqrt(INDEX(t9, 0, 0).real);
struct matrix *t10 = matrix_create_empty(1, 1);
INDEX(t10, 0, 0).real = INDEX(t8, 0, 0).real / INDEX(t9, 0, 0).real;
struct matrix *t11 = matrix_create_empty(1, 1);
INDEX(t11, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t12 = matrix_create_empty(1, 1);
INDEX(t12, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t12, 0, 0).real = sqrt(INDEX(t12, 0, 0).real);
struct matrix *t13 = matrix_create_empty(1, 1);
INDEX(t13, 0, 0).real = INDEX(t11, 0, 0).real / INDEX(t12, 0, 0).real;
struct matrix *t14 = matrix_create_empty(1, 1);
INDEX(t14, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t15 = matrix_create_empty(1, 1);
INDEX(t15, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t15, 0, 0).real = sqrt(INDEX(t15, 0, 0).real);
struct matrix *t16 = matrix_create_empty(1, 1);
INDEX(t16, 0, 0).real = INDEX(t14, 0, 0).real / INDEX(t15, 0, 0).real;
struct matrix *t17 = matrix_create_empty(1, 1);
INDEX(t17, 0, 0) = complex_create(-1.000000, 0.000000);
struct matrix *t18 = matrix_create_empty(1, 1);
INDEX(t18, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t19 = matrix_create_empty(1, 1);
INDEX(t19, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t19, 0, 0).real = sqrt(INDEX(t19, 0, 0).real);
struct matrix *t20 = matrix_create_empty(1, 1);
INDEX(t20, 0, 0).real = INDEX(t18, 0, 0).real / INDEX(t19, 0, 0).real;
struct matrix *t21 = matrix_mul(t17, t20);
quantum_gate *H = quantum_gate_create(2);
INDEX(H, 0, 0) = INDEX(t10, 0, 0);
INDEX(H, 0, 1) = INDEX(t13, 0, 0);
INDEX(H, 1, 0) = INDEX(t16, 0, 0);
INDEX(H, 1, 1) = INDEX(t21, 0, 0);
qubit *t22 = quantum_state_create(0, 2);
qubit *t23 = quantum_state_create(0, 2);
quantum_state *t24 = vector_get_dual(t23);
struct matrix *t25 = matrix_mul(t22, t24);
struct matrix *t26 = matrix_tensor_product(t25, I);
qubit *t27 = quantum_state_create(1, 2);
qubit *t28 = quantum_state_create(1, 2);
quantum_state *t29 = vector_get_dual(t28);
struct matrix *t30 = matrix_mul(t27, t29);
struct matrix *t31 = matrix_tensor_product(t30, X);
struct matrix *t32 = matrix_add(t26, t31);
quantum_gate *CNOT = t32;
qubit *t33 = quantum_state_create(1, 2);
qubit *t34 = quantum_state_create(1, 2);
quantum_state *t35 = matrix_tensor_product(t33, t34);
struct matrix *t36 = matrix_create_empty(1, 1);
INDEX(t36, 0, 0) = complex_create(0.000000, 0.000000);
quantum_gate *t37 = NULL;
for(unsigned int i = 0; i < t35->rows;) {
	if(i < INDEX(t36, 0, 0).real * 2 || i > INDEX(t36, 0, 0).real * 2) {
		if(!t37) t37 = quantum_gate_create(2);
		else t37 = matrix_tensor_product(t37, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= INDEX(t36, 0, 0).real * 2) {
		if(!t37) t37 = H;
		else t37 = matrix_tensor_product(t37, H);
		i += (INDEX(t36, 0, 0).real + 1) * 2;
	}
}
quantum_state *t38 = matrix_mul(t37, t35);
quantum_state *t39 = matrix_mul(CNOT, t38);
qm_result *t40 = quantum_state_measure(t39);
quantum_state *t41 = t40->state;
printf(CYN"Quantum state of the system after measurement: \n"GRN);
matrix_print(t41);
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t40->value);
struct matrix *t42 = matrix_create_empty(1, 1);
INDEX(t42, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t43 = matrix_create_empty(1, 1);
INDEX(t43, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t43, 0, 0).real = sqrt(INDEX(t43, 0, 0).real);
struct matrix *t44 = matrix_create_empty(1, 1);
INDEX(t44, 0, 0).real = INDEX(t42, 0, 0).real / INDEX(t43, 0, 0).real;
qubit *t45 = quantum_state_create(0, 2);
qubit *t46 = quantum_state_create(1, 2);
struct matrix *t47 = matrix_tensor_product(t45, t46);
struct matrix *t48 = matrix_mul(t44, t47);
struct matrix *t49 = matrix_create_empty(1, 1);
INDEX(t49, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t50 = matrix_create_empty(1, 1);
INDEX(t50, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t50, 0, 0).real = sqrt(INDEX(t50, 0, 0).real);
struct matrix *t51 = matrix_create_empty(1, 1);
INDEX(t51, 0, 0).real = INDEX(t49, 0, 0).real / INDEX(t50, 0, 0).real;
qubit *t52 = quantum_state_create(1, 2);
qubit *t53 = quantum_state_create(0, 2);
struct matrix *t54 = matrix_tensor_product(t52, t53);
struct matrix *t55 = matrix_mul(t51, t54);
struct matrix *t56 = matrix_sub(t48, t55);
quantum_state *t57 = matrix_mul(CNOT, t56);
struct matrix *t58 = matrix_create_empty(1, 1);
INDEX(t58, 0, 0) = complex_create(0.000000, 0.000000);
quantum_gate *t59 = NULL;
for(unsigned int i = 0; i < t57->rows;) {
	if(i < INDEX(t58, 0, 0).real * 2 || i > INDEX(t58, 0, 0).real * 2) {
		if(!t59) t59 = quantum_gate_create(2);
		else t59 = matrix_tensor_product(t59, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= INDEX(t58, 0, 0).real * 2) {
		if(!t59) t59 = H;
		else t59 = matrix_tensor_product(t59, H);
		i += (INDEX(t58, 0, 0).real + 1) * 2;
	}
}
quantum_state *t60 = matrix_mul(t59, t57);
qm_result *t61 = quantum_state_measure(t60);
quantum_state *t62 = t61->state;
printf(CYN"Quantum state of the system after measurement: \n"GRN);
matrix_print(t62);
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t61->value);
E
return 0;
}
