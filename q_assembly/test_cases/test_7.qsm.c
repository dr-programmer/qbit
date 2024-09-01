#include <stdio.h>
#include <math.h>
#include <time.h>
#define SMART_DEALLOCATION
#include "qbit.h"

int main() {S
srand(time(0));
struct matrix *t0 = matrix_create_empty(1, 1);
t0->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t1 = matrix_create_empty(1, 1);
t1->fields[0][0] = complex_create(0.000000, 0.000000);
struct matrix *t2 = matrix_create_empty(1, 1);
t2->fields[0][0] = complex_create(0.000000, 0.000000);
struct matrix *t3 = matrix_create_empty(1, 1);
t3->fields[0][0] = complex_create(1.000000, 0.000000);
quantum_gate *I = quantum_gate_create(2);
I->fields[0][0] = t0->fields[0][0];
I->fields[0][1] = t1->fields[0][0];
I->fields[1][0] = t2->fields[0][0];
I->fields[1][1] = t3->fields[0][0];
struct matrix *t4 = matrix_create_empty(1, 1);
t4->fields[0][0] = complex_create(0.000000, 0.000000);
struct matrix *t5 = matrix_create_empty(1, 1);
t5->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t6 = matrix_create_empty(1, 1);
t6->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t7 = matrix_create_empty(1, 1);
t7->fields[0][0] = complex_create(0.000000, 0.000000);
quantum_gate *X = quantum_gate_create(2);
X->fields[0][0] = t4->fields[0][0];
X->fields[0][1] = t5->fields[0][0];
X->fields[1][0] = t6->fields[0][0];
X->fields[1][1] = t7->fields[0][0];
struct matrix *t8 = matrix_create_empty(1, 1);
t8->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t9 = matrix_create_empty(1, 1);
t9->fields[0][0] = complex_create(2.000000, 0.000000);
t9->fields[0][0].real = sqrt(t9->fields[0][0].real);
struct matrix *t10 = matrix_create_empty(1, 1);
t10->fields[0][0].real = t8->fields[0][0].real / t9->fields[0][0].real;
struct matrix *t11 = matrix_create_empty(1, 1);
t11->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t12 = matrix_create_empty(1, 1);
t12->fields[0][0] = complex_create(2.000000, 0.000000);
t12->fields[0][0].real = sqrt(t12->fields[0][0].real);
struct matrix *t13 = matrix_create_empty(1, 1);
t13->fields[0][0].real = t11->fields[0][0].real / t12->fields[0][0].real;
struct matrix *t14 = matrix_create_empty(1, 1);
t14->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t15 = matrix_create_empty(1, 1);
t15->fields[0][0] = complex_create(2.000000, 0.000000);
t15->fields[0][0].real = sqrt(t15->fields[0][0].real);
struct matrix *t16 = matrix_create_empty(1, 1);
t16->fields[0][0].real = t14->fields[0][0].real / t15->fields[0][0].real;
struct matrix *t17 = matrix_create_empty(1, 1);
t17->fields[0][0] = complex_create(-1.000000, 0.000000);
struct matrix *t18 = matrix_create_empty(1, 1);
t18->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t19 = matrix_create_empty(1, 1);
t19->fields[0][0] = complex_create(2.000000, 0.000000);
t19->fields[0][0].real = sqrt(t19->fields[0][0].real);
struct matrix *t20 = matrix_create_empty(1, 1);
t20->fields[0][0].real = t18->fields[0][0].real / t19->fields[0][0].real;
struct matrix *t21 = matrix_mul(t17, t20);
quantum_gate *H = quantum_gate_create(2);
H->fields[0][0] = t10->fields[0][0];
H->fields[0][1] = t13->fields[0][0];
H->fields[1][0] = t16->fields[0][0];
H->fields[1][1] = t21->fields[0][0];
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
t36->fields[0][0] = complex_create(0.000000, 0.000000);
quantum_gate *t37 = NULL;
for(unsigned int i = 0; i < t35->rows;) {
	if(i < t36->fields[0][0].real * 2 || i > t36->fields[0][0].real * 2) {
		if(!t37) t37 = quantum_gate_create(2);
		else t37 = matrix_tensor_product(t37, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= t36->fields[0][0].real * 2) {
		if(!t37) t37 = H;
		else t37 = matrix_tensor_product(t37, H);
		i += (t36->fields[0][0].real + 1) * 2;
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
t42->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t43 = matrix_create_empty(1, 1);
t43->fields[0][0] = complex_create(2.000000, 0.000000);
t43->fields[0][0].real = sqrt(t43->fields[0][0].real);
struct matrix *t44 = matrix_create_empty(1, 1);
t44->fields[0][0].real = t42->fields[0][0].real / t43->fields[0][0].real;
qubit *t45 = quantum_state_create(0, 2);
qubit *t46 = quantum_state_create(1, 2);
struct matrix *t47 = matrix_tensor_product(t45, t46);
struct matrix *t48 = matrix_mul(t44, t47);
struct matrix *t49 = matrix_create_empty(1, 1);
t49->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t50 = matrix_create_empty(1, 1);
t50->fields[0][0] = complex_create(2.000000, 0.000000);
t50->fields[0][0].real = sqrt(t50->fields[0][0].real);
struct matrix *t51 = matrix_create_empty(1, 1);
t51->fields[0][0].real = t49->fields[0][0].real / t50->fields[0][0].real;
qubit *t52 = quantum_state_create(1, 2);
qubit *t53 = quantum_state_create(0, 2);
struct matrix *t54 = matrix_tensor_product(t52, t53);
struct matrix *t55 = matrix_mul(t51, t54);
struct matrix *t56 = matrix_sub(t48, t55);
quantum_state *t57 = matrix_mul(CNOT, t56);
struct matrix *t58 = matrix_create_empty(1, 1);
t58->fields[0][0] = complex_create(0.000000, 0.000000);
quantum_gate *t59 = NULL;
for(unsigned int i = 0; i < t57->rows;) {
	if(i < t58->fields[0][0].real * 2 || i > t58->fields[0][0].real * 2) {
		if(!t59) t59 = quantum_gate_create(2);
		else t59 = matrix_tensor_product(t59, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= t58->fields[0][0].real * 2) {
		if(!t59) t59 = H;
		else t59 = matrix_tensor_product(t59, H);
		i += (t58->fields[0][0].real + 1) * 2;
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
