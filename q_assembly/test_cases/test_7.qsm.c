#include <stdio.h>
#include <math.h>
#include <time.h>
#define SMART_DEALLOCATION
#include "qbit.h"
extern unsigned short cuda_enabled;

int main() {S
srand(time(0));
cuda_enabled = 0;
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
qubit *t35 = quantum_state_create(1, 2);
qubit *t36 = quantum_state_create(1, 2);
quantum_state *t37 = matrix_tensor_product(t35, t36);
struct matrix *t38 = matrix_create_empty(1, 1);
INDEX(t38, 0, 0) = complex_create(0.000000, 0.000000);
quantum_gate *t39 = NULL;
{
const unsigned int qubits_count = log2(t37->rows);
const unsigned int preceding_qubits_count = INDEX(t38, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t38, 0, 0).real - INDEX(t38, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t38, 0, 0).real + 1);
if(preceding_qubits_count) t39 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t39 == NULL) t39 = H;
else t39 = matrix_tensor_product(t39, H);
if(proceeding_qubits_count) t39 = 
	matrix_tensor_product(t39, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t40 = matrix_mul(t39, t37);
if(t40->columns != 1) 
	t40 = matrix_mul(t40, matrix_get_adjoint(t39));
quantum_state *t41 = matrix_mul(CNOT, t40);
if(t41->columns != 1) 
	t41 = matrix_mul(t41, matrix_get_adjoint(CNOT));
qm_result *t42 = quantum_state_measure(t41);
quantum_state *t43 = t42->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t42->value);
struct matrix *t44 = matrix_create_empty(1, 1);
INDEX(t44, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t45 = matrix_create_empty(1, 1);
INDEX(t45, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t45, 0, 0).real = sqrt(INDEX(t45, 0, 0).real);
struct matrix *t46 = matrix_create_empty(1, 1);
INDEX(t46, 0, 0).real = INDEX(t44, 0, 0).real / INDEX(t45, 0, 0).real;
qubit *t47 = quantum_state_create(0, 2);
qubit *t48 = quantum_state_create(1, 2);
struct matrix *t49 = matrix_tensor_product(t47, t48);
struct matrix *t50 = matrix_mul(t46, t49);
struct matrix *t51 = matrix_create_empty(1, 1);
INDEX(t51, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t52 = matrix_create_empty(1, 1);
INDEX(t52, 0, 0) = complex_create(2.000000, 0.000000);
INDEX(t52, 0, 0).real = sqrt(INDEX(t52, 0, 0).real);
struct matrix *t53 = matrix_create_empty(1, 1);
INDEX(t53, 0, 0).real = INDEX(t51, 0, 0).real / INDEX(t52, 0, 0).real;
qubit *t54 = quantum_state_create(1, 2);
qubit *t55 = quantum_state_create(0, 2);
struct matrix *t56 = matrix_tensor_product(t54, t55);
struct matrix *t57 = matrix_mul(t53, t56);
struct matrix *t58 = matrix_sub(t50, t57);
quantum_state *t59 = matrix_mul(CNOT, t58);
if(t59->columns != 1) 
	t59 = matrix_mul(t59, matrix_get_adjoint(CNOT));
struct matrix *t60 = matrix_create_empty(1, 1);
INDEX(t60, 0, 0) = complex_create(0.000000, 0.000000);
quantum_gate *t61 = NULL;
{
const unsigned int qubits_count = log2(t59->rows);
const unsigned int preceding_qubits_count = INDEX(t60, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t60, 0, 0).real - INDEX(t60, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t60, 0, 0).real + 1);
if(preceding_qubits_count) t61 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t61 == NULL) t61 = H;
else t61 = matrix_tensor_product(t61, H);
if(proceeding_qubits_count) t61 = 
	matrix_tensor_product(t61, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t62 = matrix_mul(t61, t59);
if(t62->columns != 1) 
	t62 = matrix_mul(t62, matrix_get_adjoint(t61));
qm_result *t63 = quantum_state_measure(t62);
quantum_state *t64 = t63->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t63->value);
qubit *t65 = quantum_state_create(0, 2);
struct matrix *t66 = matrix_mul(H, t65);
quantum_gate *minus = t66;
struct matrix *t67 = matrix_mul(H, minus);
quantum_state *t68 = matrix_tensor_product(minus, t67);
qm_result *t69 = quantum_state_measure(t68);
quantum_state *t70 = t69->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t69->value);
qubit *t71 = quantum_state_create(0, 2);
struct matrix *t72 = matrix_create_empty(1, 1);
INDEX(t72, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t73 = matrix_tensor_product_n_times(t71, INDEX(t72, 0, 0).real);
qubit *t74 = quantum_state_create(1, 2);
struct matrix *t75 = matrix_create_empty(1, 1);
INDEX(t75, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t76 = matrix_tensor_product_n_times(t74, INDEX(t75, 0, 0).real);
qubit *t77 = quantum_state_create(1, 2);
struct matrix *t78 = matrix_mul(H, t77);
quantum_state *t79 = matrix_tensor_product(t76, t78);
quantum_state *t80 = matrix_tensor_product(t73, t79);
struct matrix *t81 = matrix_create_empty(1, 1);
INDEX(t81, 0, 0) = complex_create(3.000000, 0.000000);
struct matrix *t82 = matrix_tensor_product_n_times(H, INDEX(t81, 0, 0).real);
struct matrix *t83 = matrix_create_empty(1, 1);
INDEX(t83, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t84 = matrix_create_empty(1, 1);
INDEX(t84, 0, 0) = complex_create(2.000000, 0.000000);
quantum_gate *t85 = NULL;
{
const unsigned int qubits_count = log2(t80->rows);
const unsigned int preceding_qubits_count = INDEX(t83, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t84, 0, 0).real - INDEX(t83, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t84, 0, 0).real + 1);
if(preceding_qubits_count) t85 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t85 == NULL) t85 = t82;
else t85 = matrix_tensor_product(t85, t82);
if(proceeding_qubits_count) t85 = 
	matrix_tensor_product(t85, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t86 = matrix_mul(t85, t80);
if(t86->columns != 1) 
	t86 = matrix_mul(t86, matrix_get_adjoint(t85));
struct matrix *t87 = matrix_create_empty(1, 1);
INDEX(t87, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t88 = matrix_tensor_product_n_times(H, INDEX(t87, 0, 0).real);
struct matrix *t89 = matrix_create_empty(1, 1);
INDEX(t89, 0, 0) = complex_create(3.000000, 0.000000);
struct matrix *t90 = matrix_create_empty(1, 1);
INDEX(t90, 0, 0) = complex_create(4.000000, 0.000000);
quantum_gate *t91 = NULL;
{
const unsigned int qubits_count = log2(t86->rows);
const unsigned int preceding_qubits_count = INDEX(t89, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t90, 0, 0).real - INDEX(t89, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t90, 0, 0).real + 1);
if(preceding_qubits_count) t91 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t91 == NULL) t91 = t88;
else t91 = matrix_tensor_product(t91, t88);
if(proceeding_qubits_count) t91 = 
	matrix_tensor_product(t91, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t92 = matrix_mul(t91, t86);
if(t92->columns != 1) 
	t92 = matrix_mul(t92, matrix_get_adjoint(t91));
qm_result *t93 = quantum_state_measure_subsystem(t92, 4, 4);
quantum_state *t94 = t93->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t93->value);
qm_result *t95 = quantum_state_measure_subsystem(t94, 0, 2);
quantum_state *t96 = t95->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t95->value);
qm_result *t97 = quantum_state_measure_subsystem(t96, 4, 4);
quantum_state *t98 = t97->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t97->value);
qm_result *t99 = quantum_state_measure(t98);
quantum_state *t100 = t99->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t99->value);
E
return 0;
}
