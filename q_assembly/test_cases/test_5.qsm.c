#include <stdio.h>
#include <math.h>
#include <time.h>
#define SMART_DEALLOCATION
#include "../../qbit.h"

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
quantum_gate *PARAM_GATE = t32;
struct matrix *t33 = matrix_create_empty(1, 1);
t33->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t34 = matrix_create_empty(1, 1);
t34->fields[0][0] = complex_create(0.000000, 0.000000);
quantum_state *t35 = matrix_create_empty(2, 1);
t35->fields[0][0] = t33->fields[0][0];
t35->fields[1][0] = t34->fields[0][0];
struct matrix *t36 = matrix_create_empty(1, 1);
t36->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t37 = matrix_create_empty(1, 1);
t37->fields[0][0] = complex_create(2.000000, 0.000000);
t37->fields[0][0].real = sqrt(t37->fields[0][0].real);
struct matrix *t38 = matrix_create_empty(1, 1);
t38->fields[0][0].real = t36->fields[0][0].real / t37->fields[0][0].real;
struct matrix *t39 = matrix_create_empty(1, 1);
t39->fields[0][0] = complex_create(-1.000000, 0.000000);
struct matrix *t40 = matrix_create_empty(1, 1);
t40->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t41 = matrix_mul(t39, t40);
struct matrix *t42 = matrix_create_empty(1, 1);
t42->fields[0][0] = complex_create(1.000000, 0.000000);
struct matrix *t43 = matrix_mul(t41, t42);
struct matrix *t44 = matrix_create_empty(1, 1);
t44->fields[0][0] = complex_create(2.000000, 0.000000);
t44->fields[0][0].real = sqrt(t44->fields[0][0].real);
struct matrix *t45 = matrix_create_empty(1, 1);
t45->fields[0][0].real = t43->fields[0][0].real / t44->fields[0][0].real;
quantum_state *t46 = matrix_create_empty(2, 1);
t46->fields[0][0] = t38->fields[0][0];
t46->fields[1][0] = t45->fields[0][0];
quantum_state *t47 = matrix_tensor_product(t35, t46);
struct matrix *t48 = matrix_tensor_product(H, I);
struct matrix *t49 = matrix_create_empty(1, 1);
t49->fields[0][0] = complex_create(0.000000, 0.000000);
struct matrix *t50 = matrix_create_empty(1, 1);
t50->fields[0][0] = complex_create(1.000000, 0.000000);
quantum_gate *t51 = NULL;
for(unsigned int i = 0; i < t47->rows;) {
	if(i < t49->fields[0][0].real * 2 || i > t50->fields[0][0].real * 2) {
		if(!t51) t51 = quantum_gate_create(2);
		else t51 = matrix_tensor_product(t51, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= t50->fields[0][0].real * 2) {
		if(!t51) t51 = t48;
		else t51 = matrix_tensor_product(t51, t48);
		i += (t50->fields[0][0].real + 1) * 2;
	}
}
quantum_state *t52 = matrix_mul(t51, t47);
quantum_state *t53 = matrix_mul(PARAM_GATE, t52);
struct matrix *t54 = matrix_create_empty(1, 1);
t54->fields[0][0] = complex_create(0.000000, 0.000000);
quantum_gate *t55 = NULL;
for(unsigned int i = 0; i < t53->rows;) {
	if(i < t54->fields[0][0].real * 2 || i > t54->fields[0][0].real * 2) {
		if(!t55) t55 = quantum_gate_create(2);
		else t55 = matrix_tensor_product(t55, quantum_gate_create(2));
		i+=2;
	}
	else if(i <= t54->fields[0][0].real * 2) {
		if(!t55) t55 = H;
		else t55 = matrix_tensor_product(t55, H);
		i += (t54->fields[0][0].real + 1) * 2;
	}
}
quantum_state *t56 = matrix_mul(t55, t53);
qm_result *t57 = quantum_state_measure(t56);
quantum_state *t58 = t57->state;
printf(CYN"Quantum state of the system after measurement: \n"GRN);
matrix_print(t58);
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t57->value);
qm_result *t59 = quantum_state_measure_subsystem(t58, 0, 2);
quantum_state *t60 = t59->state;
printf(CYN"Quantum state of the system after measurement: \n"GRN);
matrix_print(t60);
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t59->value);
E
return 0;
}
