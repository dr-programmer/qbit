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
quantum_gate *PARAM_GATE = t32;
struct matrix *t33 = matrix_create_empty(1, 1);
INDEX(t33, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t34 = matrix_tensor_product_n_times(H, INDEX(t33, 0, 0).real);
struct matrix *t35 = matrix_tensor_product(t34, I);
struct matrix *t36 = matrix_create_empty(1, 1);
INDEX(t36, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t37 = matrix_tensor_product_n_times(H, INDEX(t36, 0, 0).real);
struct matrix *t38 = matrix_tensor_product(I, t37);
struct matrix *t39 = matrix_create_empty(1, 1);
INDEX(t39, 0, 0) = complex_create(5.000000, 0.000000);
struct matrix *t40 = matrix_create_empty(1, 1);
INDEX(t40, 0, 0) = complex_create(0.000000, 2.000000);
struct matrix *t41 = matrix_create_empty(1, 1);
INDEX(t41, 0, 0) = complex_create(3.000000, 0.000000);
struct matrix *t42 = matrix_add(t40, t41);
struct matrix *t43 = matrix_create_empty(1, 1);
INDEX(t43, 0, 0) = complex_pow(INDEX(t39, 0, 0), INDEX(t42, 0, 0));
struct matrix *t44 = matrix_mul(t38, t43);
struct matrix *t45 = matrix_add(t35, t44);
quantum_gate *TESTING = t45;
qubit *t46 = quantum_state_create(0, 2);
qubit *t47 = quantum_state_create(1, 2);
struct matrix *t48 = matrix_mul(H, t47);
quantum_state *t49 = matrix_tensor_product(t46, t48);
struct matrix *t50 = matrix_tensor_product(H, I);
struct matrix *t51 = matrix_create_empty(1, 1);
INDEX(t51, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t52 = matrix_create_empty(1, 1);
INDEX(t52, 0, 0) = complex_create(1.000000, 0.000000);
quantum_gate *t53 = NULL;
for(unsigned int i = 0; i < t49->rows;) {
	if(i < INDEX(t51, 0, 0).real * 2 || i > INDEX(t52, 0, 0).real * 2) {
		if(!t53) t53 = quantum_gate_create(2);
		else t53 = matrix_tensor_product(t53, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= INDEX(t52, 0, 0).real * 2) {
		if(!t53) t53 = t50;
		else t53 = matrix_tensor_product(t53, t50);
		i += (INDEX(t52, 0, 0).real + 1) * 2;
	}
}
quantum_state *t54 = matrix_mul(t53, t49);
quantum_state *t55 = matrix_mul(PARAM_GATE, t54);
struct matrix *t56 = matrix_create_empty(1, 1);
INDEX(t56, 0, 0) = complex_create(0.000000, 0.000000);
quantum_gate *t57 = NULL;
for(unsigned int i = 0; i < t55->rows;) {
	if(i < INDEX(t56, 0, 0).real * 2 || i > INDEX(t56, 0, 0).real * 2) {
		if(!t57) t57 = quantum_gate_create(2);
		else t57 = matrix_tensor_product(t57, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= INDEX(t56, 0, 0).real * 2) {
		if(!t57) t57 = H;
		else t57 = matrix_tensor_product(t57, H);
		i += (INDEX(t56, 0, 0).real + 1) * 2;
	}
}
quantum_state *t58 = matrix_mul(t57, t55);
qm_result *t59 = quantum_state_measure(t58);
quantum_state *t60 = t59->state;
printf(CYN"Quantum state of the system after measurement: \n"GRN);
matrix_print(t60);
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t59->value);
qm_result *t61 = quantum_state_measure_subsystem(t60, 0, 2);
quantum_state *t62 = t61->state;
printf(CYN"Quantum state of the system after measurement: \n"GRN);
matrix_print(t62);
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t61->value);
E
return 0;
}
