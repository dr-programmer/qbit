#define SMART_DEALLOCATION

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "smart_allocation/smart_allocation.h"
#include "linear_algebra/linear_algebra.h"
#include "qubits.h"
#include "operators.h"
#include "algorithms.h"
#include "colors.h"
#include "error.h"
#include "structures.h"
#include "scope.h"

extern FILE *yyin;
extern int yyparse();

extern struct decl *parser_result;

struct scope *symbol_table = NULL;

FILE *result_file = NULL;

unsigned short show_pcode = 0;
unsigned short gen_qset = 0;
unsigned short compile_time_calculations = 0;

int main(int argc, char **argv) {S
    //smart_allocation_setup();

    srand(time(0));

    if(argc == 1) {
    S
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

        int check0 = smart_free(hadamard_minus);
        int check1 = smart_free(hadamard_minus);
        printf("Free 0: %d \nFree 1: %d \n", check0, check1);

        printf("\nDeutsch algorithm: %hd \n", algorithm_deutsch(quantum_gate_create_cnot()));

        struct complex num = complex_create(3.6, 3.2);
        struct complex num_pow = complex_create(4.5, 1.2);
        struct complex num_result = complex_pow(num, num_pow);
        printf("\n(");
        complex_print(num);
        printf(") to the power of (");
        complex_print(num_pow);
        printf("):\nresult = ");
        complex_print(num_result);
        printf("\n");

        unsigned int n = 2;
        struct matrix *hadamard_n_times = matrix_tensor_product_n_times(hadamard, n);
        printf("\nThe Hadamard gate tensor product %u times with itself: \n", n);
        matrix_print(hadamard_n_times);
        C
        exit(0);
    E
    }
    char *name_of_starting_file = NULL;
    char *name_of_file = "a.out";
    for(unsigned int i = 1; i < argc; i++) {
        if(!strcmp(argv[i], "--show-pcode")) {
            show_pcode = 1;
        }
        else if(!strcmp(argv[i], "-gen-qset")) {
            gen_qset = 1;
            if(++i >= argc) {
                fprintf(stderr, "Wrong cli flags! \n");
                C
                exit(ERROR_WRONG_CLI_FLAGS);
            }
            name_of_file = argv[i];
        }
        else if(!strcmp(argv[i], "--fast-run")) {
            compile_time_calculations = 1;
        }
        else {
            name_of_starting_file = argv[i];
        }
    }
    yyin = fopen(name_of_starting_file, "r");
    if(yyin == NULL) {
        fprintf(stderr, "Error opening file %s \n", argv[1]);
        C
        exit(ERROR_OPENING_FILE);
    }
    if(gen_qset) printf("Name of result file = "CYN"%s"RESET" \n", name_of_file);
    if(yyparse() == 0) {
        printf("Parse "GRN"successful"RESET"! \n");
        if(show_pcode) decl_print(parser_result, 0);

        scope_enter();
        decl_resolve(parser_result);
        scope_exit();

        decl_typecheck(parser_result);

        if(!error_count) {
            if(gen_qset) {S
                char *result_file_name = 
                    (char *)smart_allocate(strlen(name_of_starting_file) + 3, sizeof(char));
                if(result_file_name == NULL) {
                    fprintf(stderr, "Cannot allocate memory! \n");
                    C
                    exit(ERROR_ALLOCATING_MEMORY);
                }
                strcpy(result_file_name, name_of_starting_file);
                strcat(result_file_name, ".c");
                result_file = fopen(result_file_name, "w");
                if(result_file == NULL) {
                    fprintf(stderr, "Error opening file %s \n", result_file_name);
                    C
                    exit(ERROR_OPENING_FILE);
                }
                fprintf(result_file, "#include <stdio.h>\n"
                                        "#include <math.h>\n"
                                        "#include <time.h>\n"
                                        "#define SMART_DEALLOCATION\n"
                                        "#include \"../../qbit.h\"\n");
                fprintf(result_file, "\nint main() {S\nsrand(time(0));\n");
                decl_codegen(parser_result);
                fprintf(result_file, "E\nreturn 0;\n}\n");
                fclose(result_file);

                char *compile_command = (char *)smart_allocate(
                    strlen(result_file_name) + strlen(name_of_file) + 36, 
                    sizeof(char)
                );
                if(compile_command == NULL) {
                    fprintf(stderr, "Cannot allocate memory! \n");
                    C
                    exit(ERROR_ALLOCATING_MEMORY);
                }
                sprintf(compile_command, "gcc -x c %s -o %s -lqbit -lm", 
                                                    result_file_name, 
                                                    name_of_file);
                system(compile_command);
            E
            }
            else decl_coderun(parser_result);
        }
        printf("\nProgram compiled with %d error/s \n", error_count);
    }
    else {
        printf("Parse "RED"failed"RESET". \n");
    }

    fclose(yyin);

    //smart_allocation_free();
E
    return 0;
}