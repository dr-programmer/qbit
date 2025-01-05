#include <stdio.h>
#include <math.h>
#include <time.h>
#define SMART_DEALLOCATION
#include "qbit.h"

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
struct matrix *t94 = matrix_create_empty(1, 1);
INDEX(t94, 0, 0) = complex_create(4.000000, 0.000000);
qm_result *t93 = NULL;
{
const unsigned int start = INDEX(t94, 0, 0).real;
const unsigned int end = INDEX(t94, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t92->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t93 = quantum_state_measure(t92);
else t93 = quantum_state_measure_subsystem(t92, start, end);
}
quantum_state *t95 = t93->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t93->value);
struct matrix *t97 = matrix_create_empty(1, 1);
INDEX(t97, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t98 = matrix_create_empty(1, 1);
INDEX(t98, 0, 0) = complex_create(2.000000, 0.000000);
qm_result *t96 = NULL;
{
const unsigned int start = INDEX(t97, 0, 0).real;
const unsigned int end = INDEX(t98, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t95->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t96 = quantum_state_measure(t95);
else t96 = quantum_state_measure_subsystem(t95, start, end);
}
quantum_state *t99 = t96->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t96->value);
struct matrix *t101 = matrix_create_empty(1, 1);
INDEX(t101, 0, 0) = complex_create(4.000000, 0.000000);
qm_result *t100 = NULL;
{
const unsigned int start = INDEX(t101, 0, 0).real;
const unsigned int end = INDEX(t101, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t99->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t100 = quantum_state_measure(t99);
else t100 = quantum_state_measure_subsystem(t99, start, end);
}
quantum_state *t102 = t100->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t100->value);
qm_result *t103 = quantum_state_measure(t102);
quantum_state *t104 = t103->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t103->value);
qubit *t105 = quantum_state_create(0, 2);
struct matrix *t106 = matrix_create_empty(1, 1);
INDEX(t106, 0, 0) = complex_create(3.000000, 0.000000);
struct matrix *t107 = matrix_tensor_product_n_times(t105, INDEX(t106, 0, 0).real);
qubit *t108 = quantum_state_create(1, 2);
struct matrix *t109 = matrix_create_empty(1, 1);
INDEX(t109, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t110 = matrix_tensor_product_n_times(t108, INDEX(t109, 0, 0).real);
qubit *t111 = quantum_state_create(0, 2);
quantum_state *t112 = matrix_tensor_product(t110, t111);
quantum_state *t113 = matrix_tensor_product(t107, t112);
struct matrix *t115 = matrix_create_empty(1, 1);
INDEX(t115, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t116 = matrix_create_empty(1, 1);
INDEX(t116, 0, 0) = complex_create(3.000000, 0.000000);
qm_result *t114 = NULL;
{
const unsigned int start = INDEX(t115, 0, 0).real;
const unsigned int end = INDEX(t116, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t113->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t114 = quantum_state_measure(t113);
else t114 = quantum_state_measure_subsystem(t113, start, end);
}
quantum_state *t117 = t114->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t114->value);
struct matrix *t119 = matrix_create_empty(1, 1);
INDEX(t119, 0, 0) = complex_create(5.000000, 0.000000);
qm_result *t118 = NULL;
{
const unsigned int start = INDEX(t119, 0, 0).real;
const unsigned int end = INDEX(t119, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t117->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t118 = quantum_state_measure(t117);
else t118 = quantum_state_measure_subsystem(t117, start, end);
}
quantum_state *t120 = t118->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t118->value);
qubit *t121 = quantum_state_create(0, 2);
qubit *t122 = quantum_state_create(0, 2);
qubit *t123 = quantum_state_create(0, 2);
quantum_state *t124 = matrix_tensor_product(t122, t123);
quantum_state *t125 = matrix_tensor_product(t121, t124);
struct matrix *t126 = matrix_create_empty(1, 1);
INDEX(t126, 0, 0) = complex_create(2.000000, 0.000000);
struct matrix *t127 = matrix_tensor_product_n_times(H, INDEX(t126, 0, 0).real);
struct matrix *t128 = matrix_create_empty(1, 1);
INDEX(t128, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t129 = matrix_create_empty(1, 1);
INDEX(t129, 0, 0) = complex_create(1.000000, 0.000000);
quantum_gate *t130 = NULL;
{
const unsigned int qubits_count = log2(t125->rows);
const unsigned int preceding_qubits_count = INDEX(t128, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t129, 0, 0).real - INDEX(t128, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t129, 0, 0).real + 1);
if(preceding_qubits_count) t130 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t130 == NULL) t130 = t127;
else t130 = matrix_tensor_product(t130, t127);
if(proceeding_qubits_count) t130 = 
	matrix_tensor_product(t130, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t131 = matrix_mul(t130, t125);
if(t131->columns != 1) 
	t131 = matrix_mul(t131, matrix_get_adjoint(t130));
struct matrix *t133 = matrix_create_empty(1, 1);
INDEX(t133, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t134 = matrix_create_empty(1, 1);
INDEX(t134, 0, 0) = complex_create(1.000000, 0.000000);
qm_result *t132 = NULL;
{
const unsigned int start = INDEX(t133, 0, 0).real;
const unsigned int end = INDEX(t134, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t131->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t132 = quantum_state_measure(t131);
else t132 = quantum_state_measure_subsystem(t131, start, end);
}
quantum_state *t135 = t132->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t132->value);
struct matrix *t136 = matrix_create_empty(1, 1);
INDEX(t136, 0, 0) = complex_create(10.000000, 0.000000);
struct matrix *t137 = matrix_create_empty(1, 1);
INDEX(t137, 0, 0) = complex_create(6.000000, 0.000000);
struct matrix *t138 = matrix_sub(t136, t137);
quantum_gate *num_qubits = t138;
qubit *t139 = quantum_state_create(0, 2);
struct matrix *t140 = matrix_tensor_product_n_times(t139, INDEX(num_qubits, 0, 0).real);
qubit *t141 = quantum_state_create(0, 2);
quantum_state *t142 = matrix_tensor_product(t140, t141);
struct matrix *t143 = matrix_tensor_product_n_times(H, INDEX(num_qubits, 0, 0).real);
struct matrix *t144 = matrix_create_empty(1, 1);
INDEX(t144, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t145 = matrix_create_empty(1, 1);
INDEX(t145, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t146 = matrix_sub(num_qubits, t145);
quantum_gate *t147 = NULL;
{
const unsigned int qubits_count = log2(t142->rows);
const unsigned int preceding_qubits_count = INDEX(t144, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t146, 0, 0).real - INDEX(t144, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t146, 0, 0).real + 1);
if(preceding_qubits_count) t147 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t147 == NULL) t147 = t143;
else t147 = matrix_tensor_product(t147, t143);
if(proceeding_qubits_count) t147 = 
	matrix_tensor_product(t147, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t148 = matrix_mul(t147, t142);
if(t148->columns != 1) 
	t148 = matrix_mul(t148, matrix_get_adjoint(t147));
struct matrix *t149 = matrix_create_empty(1, 1);
INDEX(t149, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t150 = matrix_add(num_qubits, t149);
struct matrix *t151 = matrix_tensor_product_n_times(I, INDEX(t150, 0, 0).real);
quantum_state *t152 = matrix_mul(t151, t148);
if(t152->columns != 1) 
	t152 = matrix_mul(t152, matrix_get_adjoint(t151));
struct matrix *t153 = matrix_tensor_product_n_times(I, INDEX(num_qubits, 0, 0).real);
struct matrix *t154 = matrix_tensor_product(t153, I);
quantum_state *t155 = matrix_mul(t154, t152);
if(t155->columns != 1) 
	t155 = matrix_mul(t155, matrix_get_adjoint(t154));
struct matrix *t156 = matrix_sub(num_qubits, num_qubits);
quantum_gate *t157 = NULL;
{
const unsigned int qubits_count = log2(t155->rows);
const unsigned int preceding_qubits_count = INDEX(t156, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t156, 0, 0).real - INDEX(t156, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t156, 0, 0).real + 1);
if(preceding_qubits_count) t157 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t157 == NULL) t157 = I;
else t157 = matrix_tensor_product(t157, I);
if(proceeding_qubits_count) t157 = 
	matrix_tensor_product(t157, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t158 = matrix_mul(t157, t155);
if(t158->columns != 1) 
	t158 = matrix_mul(t158, matrix_get_adjoint(t157));
struct matrix *t159 = matrix_create_empty(1, 1);
INDEX(t159, 0, 0) = complex_create(2.000000, 0.000000);
quantum_gate *t160 = NULL;
{
const unsigned int qubits_count = log2(t158->rows);
const unsigned int preceding_qubits_count = INDEX(t159, 0, 0).real;
const unsigned int measured_qubits_count = 
	(INDEX(t159, 0, 0).real - INDEX(t159, 0, 0).real) + 1;
const unsigned int proceeding_qubits_count = 
	qubits_count - (INDEX(t159, 0, 0).real + 1);
if(preceding_qubits_count) t160 = 
	quantum_gate_create(pow(2, preceding_qubits_count));
if(t160 == NULL) t160 = I;
else t160 = matrix_tensor_product(t160, I);
if(proceeding_qubits_count) t160 = 
	matrix_tensor_product(t160, 
		quantum_gate_create(pow(2, proceeding_qubits_count))
	);
}
quantum_state *t161 = matrix_mul(t160, t158);
if(t161->columns != 1) 
	t161 = matrix_mul(t161, matrix_get_adjoint(t160));
struct matrix *t163 = matrix_create_empty(1, 1);
INDEX(t163, 0, 0) = complex_create(0.000000, 0.000000);
struct matrix *t164 = matrix_sub(num_qubits, num_qubits);
struct matrix *t165 = matrix_create_empty(1, 1);
INDEX(t165, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t166 = matrix_add(t164, t165);
qm_result *t162 = NULL;
{
const unsigned int start = INDEX(t163, 0, 0).real;
const unsigned int end = INDEX(t166, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t161->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t162 = quantum_state_measure(t161);
else t162 = quantum_state_measure_subsystem(t161, start, end);
}
quantum_state *t167 = t162->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t162->value);
struct matrix *t169 = matrix_sub(num_qubits, num_qubits);
struct matrix *t170 = matrix_create_empty(1, 1);
INDEX(t170, 0, 0) = complex_create(1.000000, 0.000000);
struct matrix *t171 = matrix_add(t169, t170);
qm_result *t168 = NULL;
{
const unsigned int start = INDEX(t171, 0, 0).real;
const unsigned int end = INDEX(t171, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t167->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t168 = quantum_state_measure(t167);
else t168 = quantum_state_measure_subsystem(t167, start, end);
}
quantum_state *t172 = t168->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t168->value);
struct matrix *t174 = matrix_create_empty(1, 1);
INDEX(t174, 0, 0) = complex_create(2.000000, 0.000000);
qm_result *t173 = NULL;
{
const unsigned int start = INDEX(t174, 0, 0).real;
const unsigned int end = INDEX(t174, 0, 0).real;
const unsigned int scope = end - start + 1;
const unsigned int qubits_count = log2(t172->rows);
if(scope <= 0 || scope >= qubits_count || start > qubits_count) 
	t173 = quantum_state_measure(t172);
else t173 = quantum_state_measure_subsystem(t172, start, end);
}
quantum_state *t175 = t173->state;
printf(CYN"Classical bit representation: "GRN"%d \n"RESET, t173->value);
E
return 0;
}
