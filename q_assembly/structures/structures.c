#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#define SMART_DEALLOCATION
#include "smart_allocation.h"

unsigned int error_count;

struct decl *decl_create(char *name, 
                            struct expr *value, 
                            struct expr *circuit, 
                            struct decl *next, 
                            unsigned int line) 
{
    struct decl *temp = (struct decl *)smart_allocate(1, sizeof(struct decl));
    temp->name = name;
    temp->value = value;
    temp->circuit = circuit;
    temp->next = next;
    temp->line = line;
    return temp;
}

struct expr *expr_create(expr_t kind, 
                            struct expr *left, 
                            struct expr *right, 
                            unsigned int line) 
{
    struct expr *temp = (struct expr *)smart_allocate(1, sizeof(struct expr));
    temp->kind = kind;
    temp->left = left;
    temp->right = right;
    temp->line = line;
    temp->reg = reg_create(-1, -1);
    return temp;
}

struct expr *expr_create_name(char *name, unsigned int line) {
    struct expr *temp = expr_create(EXPR_NAME, NULL, NULL, line);
    temp->name = name;
    return temp;
}
struct expr *expr_create_complex_literal(struct complex num, unsigned int line) {
    struct expr *temp = expr_create(EXPR_COMPLEX_LITERAL, NULL, NULL, line);
    temp->complex_literal = num;
    return temp;
}

void decl_print(const struct decl * const d, const unsigned short is_error) {
    if(!d) return;

    if(d->name) {
        printf("%s ( \n", d->name);
        expr_print(d->value, 1);
        printf("\n)\n");
    }
    else if(d->file_name) {
        printf("load (\"%s\")\n", d->file_name);
    }
    else {
        printf("{ \n");
        expr_print(d->value, 1);
        printf("\n}\n");
        expr_print(d->circuit, 1);
        printf("\n");
    }

    if(!is_error) decl_print(d->next, 0);
}
static void print_tabs(const int tabs) {
    if(tabs <= 0) return;

    for(unsigned int i = 0; i < tabs; i++) {
        printf("\t");
    }
}
static void print_number(const struct complex num) {
    if(num.imaginary != 0) printf("%fi", num.imaginary);
    else printf("%f", num.real);
}
void expr_print(const struct expr * const e, const int tabs) {
    if(!e) return;

    print_tabs(tabs);
    switch(e->kind) {
        case EXPR_NAME: printf("(%s)", e->name); break;
        case EXPR_COMPLEX_LITERAL: 
                            if(tabs == -1) printf("%d", (int)e->complex_literal.real);
                            else print_number(e->complex_literal);
                            break;
        case EXPR_KET: printf("|"); expr_print(e->right, -1); printf(">"); break;
        case EXPR_BRA: printf("<"); expr_print(e->left, -1); printf("|"); break;
        case EXPR_SQRT: printf("#("); expr_print(e->right, 0); printf(")"); break;
        case EXPR_ADD: printf("("); expr_print(e->left, 0); printf(" + "); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_SUB: printf("("); expr_print(e->left, 0); printf(" - "); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_MUL: printf("("); expr_print(e->left, 0); printf(" * "); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_DIV: printf("("); expr_print(e->left, 0); printf(" / "); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_MODULUS: printf("("); expr_print(e->left, 0); printf(" %% "); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_TENSOR_PRODUCT: printf("("); expr_print(e->left, 0); printf(" @ "); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_POWER: printf("("); expr_print(e->left, 0); printf("^"); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_TENSOR_PRODUCT_N_TIMES: printf("("); expr_print(e->left, 0); printf("^@"); 
                                        expr_print(e->right, 0); printf(")"); break;
        case EXPR_AND: expr_print(e->left, 0); 
                            if(e->right) {
                                printf(" && ");
                                expr_print(e->right, 0);
                            }
                            break;
        case EXPR_FIELD: expr_print(e->left, 0); 
                            if(e->right) {
                                int next_tabs = 0;
                                if(tabs == -2) {
                                    printf(" | ");
                                    next_tabs = -2;
                                }
                                else printf(", ");
                                expr_print(e->right, next_tabs);
                            }
                            break;
        case EXPR_REGISTER: printf("{"); 
                            expr_print(e->left, -2);
                            printf("}");
                            if(e->right) {
                                printf("\n");
                                expr_print(e->right, tabs);
                            }
                            break;
        case EXPR_CIRCUIT_STEP: printf(" -> ");
                            expr_print(e->left, 0); 
                            if(e->right) {
                                printf("\n");
                                expr_print(e->right, tabs);
                            }
                            break;
        case EXPR_MEASURE: printf("<"); 
                            if(e->right) {
                                printf("[");
                                expr_print(e->right, -1);
                                printf("]");
                            }
                            break;
        case EXPR_APPLY_GATE: expr_print(e->left, 0); 
                            if(e->right) {
                                printf("[");
                                expr_print(e->right, -1);
                                printf("]");
                            }
                            break;
        case EXPR_RANGE: expr_print(e->left, -1); printf(" ... "); 
                                expr_print(e->right, -1); break;
    }
}

#include "stdarg.h"

void printf_error(char *str, ...) {
    va_list argument;
    struct decl *d;
    struct expr *e;
    error_count++;
    va_start(argument, str);
    for(unsigned int i = 0; str[i] != '\0'; i++) {
        switch(str[i]) {
            case '%':
                switch(str[++i]) {
                    case 'D':
                        d = va_arg(argument, struct decl *);
                        decl_print(d, 1);
                        break;
                    case 'E':
                        e = va_arg(argument, struct expr *);
                        expr_print(e, 0);
                        break;
                    case 'd':
                        int num = va_arg(argument, int);
                        printf("%d", num);
                        break;
                    case 'c':
                        char c = va_arg(argument, int);
                        putchar(c);
                        break;
                    case 's':
                        char *s = va_arg(argument, char *);
                        printf("%s", s);
                        break;
                    case '%':
                        putchar(str[i]);
                        break;
                    default: i--; break;
                }
                break;
            default: putchar(str[i]); break;
        }
    }
    va_end(argument);
}

#include "scope.h"
#include "colors.h"
#include "error.h"

extern FILE *yyin;
extern int yyparse();
extern struct decl *parser_result;
extern int line;
extern char *global_name_of_starting_file;

extern unsigned short show_lpcode;

void decl_resolve(struct decl * const d) {
    if(!d) return;

    if(d->name) {
        if(scope_lookup_current(d->name)) 
            printf_error(BLU"%s"RESET": "
                            RED"Error "MAG"|%s|"RESET"->"YEL"\n|%D|"RESET" on line %d \n", 
                            global_name_of_starting_file, 
                            "variable already exists", d, d->line);
        else scope_bind(d);
    }
    else if(d->file_name) {
        struct decl *original_parser_result = parser_result;
        line = 0;
        char *original_global_name_of_starting_file = global_name_of_starting_file;

        yyin = fopen(d->file_name, "r");
        global_name_of_starting_file = d->file_name;

        if(yyin == NULL) {
            fprintf(stderr, "Error opening file %s \n", d->file_name);
            C
            exit(ERROR_OPENING_FILE);
        }
        if(yyparse() == 0) {
            printf(BLU"%s"RESET": Parse "GRN"successful"RESET"! \n", d->file_name);
            d->loaded = parser_result;

            if(show_lpcode) decl_print(d->loaded, 0);

            decl_resolve(d->loaded);
        }
        else printf(BLU"%s"RESET": Parse "RED"failed"RESET". \n", d->file_name);

        parser_result = original_parser_result;
        global_name_of_starting_file = original_global_name_of_starting_file;
    }
    expr_resolve(d->value);
    expr_resolve(d->circuit);

    decl_resolve(d->next);
}
void expr_resolve(struct expr * const e) {
    if(!e) return;

    if(e->kind == EXPR_NAME) {
        e->declaration = scope_lookup(e->name);
        if(e->declaration == NULL) {
            printf_error(BLU"%s"RESET": "
                            RED"Error "MAG"|%s|"RESET"\n\t->"YEL"|%E|"RESET" on line %d \n", 
                            global_name_of_starting_file, 
                            "no declaration found", e, e->line);
        }
    }
    else {
        expr_resolve(e->left);
        expr_resolve(e->right);
    }
}

struct dimensions dimensions_create(int rows, int columns) {
    struct dimensions temp = {rows, columns};
    return temp;
}
struct dimensions get_gate_dimensions(const struct dimensions d) {
    int side = sqrt(d.columns);
    return dimensions_create(side, side);
}
void decl_typecheck(struct decl * const d) {
    if(!d) return;

    struct dimensions dimensions = dimensions_create(0, 0);
    dimensions = expr_typecheck(d->value);
    expr_typecheck(d->circuit);
    if(d->name) {
        if(dimensions.rows == 0) d->dimensions = get_gate_dimensions(dimensions);
        else d->dimensions = dimensions;
    }
    else if(d->file_name) {
        char *original_global_name_of_starting_file = global_name_of_starting_file;
        global_name_of_starting_file = d->file_name;
        decl_typecheck(d->loaded);
        global_name_of_starting_file = original_global_name_of_starting_file;
    }

    decl_typecheck(d->next);
}
struct reg reg_create(int start, int end) {
    struct reg temp = {start, end};
    return temp;
}
struct dimensions expr_typecheck(struct expr * const e) {
    if(!e) return dimensions_create(0, 0);

    struct dimensions left = expr_typecheck(e->left);
    struct dimensions right = expr_typecheck(e->right);

    struct dimensions result = dimensions_create(0, 0);

    switch(e->kind) {
        case EXPR_NAME: if(e->declaration) result = e->declaration->dimensions; break;
        case EXPR_COMPLEX_LITERAL: 
            e->reg = reg_create(e->complex_literal.real, e->complex_literal.real);
            result = dimensions_create(1, 1);
            break;
        case EXPR_KET ... EXPR_BRA: {
            int qubit_value = -1;

            if(e->right && e->right->complex_literal.real > 1) 
                qubit_value = e->right->complex_literal.real;

            else if(e->left && e->left->complex_literal.real > 1) 
                qubit_value = e->left->complex_literal.real;

            if(qubit_value != -1) 
                printf_error(BLU"%s"RESET": "RED"Error "MAG 
                    "|cannot create a 2D quantum state from the value "BLU"(%d)"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    global_name_of_starting_file, 
                    qubit_value, e, e->line);
            
            if(e->kind == EXPR_KET) result = dimensions_create(2, 1);
            else result = dimensions_create(1, 2);
            break;
        }
        case EXPR_SQRT: 
        case EXPR_MODULUS: 
            if(e->left && (left.rows != 1 || left.columns != 1 
                || right.rows != 1 || right.columns != 1)) 
                printf_error(BLU"%s"RESET": "RED"Error "MAG 
                    "|cannot apply binary real operator "BLU"(%%)"
                    MAG" between operands of dimension"BLU 
                    " [%dx%d]"MAG" and "BLU"[%dx%d]"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    global_name_of_starting_file, 
                    left.rows, left.columns, right.rows, right.columns, e, e->line);
            else if(right.rows != 1 || right.columns != 1) 
                printf_error(BLU"%s"RESET": "RED"Error "MAG 
                    "|cannot apply unitary complex operator "BLU"(#)"
                    MAG" on operand of dimension"BLU 
                    " [%dx%d]"MAG"|"RESET"\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    global_name_of_starting_file, 
                    right.rows, right.columns, e, e->line);
            
            result = dimensions_create(1, 1);
            break;
        case EXPR_TENSOR_PRODUCT: 
        case EXPR_ADD ... EXPR_DIV: {
            char operator;
            if(e->kind == EXPR_ADD) operator = '+';
            else if(e->kind == EXPR_SUB) operator = '-';
            else if(e->kind == EXPR_MUL) operator = '*';
            else if(e->kind == EXPR_DIV) operator = '/';
            else if(e->kind == EXPR_TENSOR_PRODUCT) operator = '@';
            int add_sub_check = e->kind == EXPR_ADD || e->kind == EXPR_SUB 
                        ? left.rows != right.rows || left.columns != right.columns 
                        : 1;
            int mul_check = e->kind == EXPR_MUL 
                        ? ((left.rows != 1 || left.columns != 1) 
                            && (right.rows != 1 || right.columns != 1)) 
                            && (left.columns != right.rows 
                            || (left.columns == 0 && right.rows == 0)) 
                        : 1;
            int div_check = e->kind == EXPR_DIV 
                        ? ((left.rows != 1 || left.columns != 1) 
                            || (right.rows != 1 || right.columns != 1)) 
                        : 1;
            int tensor_check = e->kind == EXPR_TENSOR_PRODUCT 
                        ? ((left.rows <= 1 && left.columns <= 1) 
                            || (right.rows <= 1 && right.columns <= 1)) 
                        : 1;
            if(add_sub_check && mul_check && div_check && tensor_check) 
                printf_error(BLU"%s"RESET": "RED"Error "MAG 
                    "|cannot apply binary operator "BLU"(%c)"MAG
                    " between operands of dimension"BLU 
                    " [%dx%d]"MAG" and "BLU"[%dx%d]"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    global_name_of_starting_file, 
                    operator, left.rows, left.columns, right.rows, right.columns, e, e->line);
            
            if(e->kind == EXPR_TENSOR_PRODUCT) {
                result.rows = left.rows * right.rows;
                result.columns = left.columns * right.columns;
            }
            else {
                if(left.rows == 1 && left.columns == 1) result = right;
                else if(right.rows == 1 && right.columns == 1) result = left;
                else {
                    result.rows = left.rows;
                    result.columns = right.columns;
                }
            }
            break;
        }
        case EXPR_POWER:
            if(left.rows != 1 || left.columns != 1 || right.rows != 1 || right.columns != 1) 
                printf_error(BLU"%s"RESET": "RED"Error "MAG 
                    "|cannot apply binary complex operator "BLU"(%c)"MAG
                    " between operands of dimension"BLU 
                    " [%dx%d]"MAG" and "BLU"[%dx%d]"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    global_name_of_starting_file, 
                    '^', left.rows, left.columns, right.rows, right.columns, e, e->line);
            result = left;
            break;
        case EXPR_TENSOR_PRODUCT_N_TIMES:
            if(right.rows != 1 || right.columns != 1 
                || e->right->complex_literal.imaginary != 0) {
                printf_error(BLU"%s"RESET": "RED"Error "MAG 
                    "|cannot apply binary operator "BLU"(%s)"MAG
                    " on an operand of dimension"BLU 
                    " [%dx%d]"MAG" with a given "BLU"non-real power"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    global_name_of_starting_file, 
                    "^@", left.rows, left.columns, e, e->line);
                result = left;
            }
            else {
                result.rows = pow(left.rows, (int)e->right->complex_literal.real);
                result.columns = pow(left.columns, (int)e->right->complex_literal.real);
            }
            break;
        case EXPR_RANGE: 
            e->reg = reg_create(
                e->left->complex_literal.real, 
                e->right->complex_literal.real
            );
            break;
        case EXPR_APPLY_GATE: if(e->right) e->reg = e->right->reg; break;
        case EXPR_MEASURE: if(e->right) e->reg = e->right->reg; break;
        case EXPR_FIELD: result = dimensions_create(0, right.columns + 1); break;
        case EXPR_REGISTER: {
            int left_dimensions;

            if(e->left->kind != EXPR_FIELD) left_dimensions = e->left->dimensions.rows;
            else left_dimensions = e->left->dimensions.columns;

            if(e->right == NULL) result = dimensions_create(left_dimensions, 1);
            else result = dimensions_create(left_dimensions 
                                                    * e->right->dimensions.rows, 
                                                1);
            break;
        }
    }

    e->dimensions = result;

    return result;
}

static quantum_operator *get_quantum_operator(const struct matrix * const m, 
                                                const struct dimensions d) 
{
    if(!m) return NULL;

    quantum_operator *result = matrix_create_empty(d.rows, d.columns);
    for(unsigned int i = 0; i < d.rows; i++) {
        for(unsigned int j = 0; j < d.columns; j++) {
            INDEX(result, i, j) = INDEX(m, 0, j + i * d.columns);
        }
    }

    return result;
}
void decl_coderun(struct decl * const d) {
    if(!d) return;

    if(d->name) {
        struct matrix *temp = expr_coderun(d->value, NULL);
        if(d->value->kind == EXPR_FIELD) temp = get_quantum_operator(temp, d->dimensions);
        d->operator = temp;
    }
    else if(d->file_name) {
        decl_coderun(d->loaded);
    }
    else {
        quantum_state *registers = expr_coderun(d->value, NULL);
        expr_coderun(d->circuit, registers);
    }

    decl_coderun(d->next);
}
struct matrix *expr_coderun(struct expr * const e, quantum_state * const regs) {
    if(!e) return NULL;

    struct matrix *left = NULL;
    struct matrix *right = NULL;

    if(regs == NULL) {
        left = expr_coderun(e->left, regs);
        right = expr_coderun(e->right, regs);
    }

    struct matrix *result = NULL;

    switch(e->kind) {
        case EXPR_NAME: result = e->declaration->operator; break;
        case EXPR_COMPLEX_LITERAL: S
            result = matrix_mul_scalar(
                e->complex_literal, 
                matrix_create(1, 1)
            );
            P(result)
            E
            break;
        case EXPR_KET: S
            result = quantum_state_create(INDEX(right, 0, 0).real, e->dimensions.rows);
            P(result)
            E
            break;
        case EXPR_BRA: {S
            quantum_state *temp = 
                quantum_state_create(INDEX(left, 0, 0).real, e->dimensions.columns);
            result = vector_get_dual(temp);
            P(result)
            E
            break;
        }
        case EXPR_SQRT: 
            INDEX(right, 0, 0).real = sqrt(INDEX(right, 0, 0).real);
            result = right;
            break;
        case EXPR_MODULUS: S
            result = matrix_mul_scalar(
                complex_create(
                    (int)INDEX(left, 0, 0).real % (int)INDEX(right, 0, 0).real, 
                    0
                ), 
                matrix_create(1, 1)
            );
            P(result)
            E
            break;
        case EXPR_ADD: S
            result = matrix_add(left, right);
            P(result)
            E
            break;
        case EXPR_SUB: S
            result = matrix_sub(left, right);
            P(result)
            E
            break;
        case EXPR_MUL: S
            result = matrix_mul(left, right);
            P(result)
            E
            break;
        case EXPR_DIV: S
            result = matrix_mul_scalar(
                complex_div(INDEX(left, 0, 0), INDEX(right, 0, 0)), 
                matrix_create(1, 1)
            );
            P(result)
            E
            break;
        case EXPR_TENSOR_PRODUCT: S
            result = matrix_tensor_product(left, right);
            P(result)
            E
            break;
        case EXPR_POWER: S
            result = matrix_mul_scalar(
                complex_pow(INDEX(left, 0, 0), INDEX(right, 0, 0)), 
                matrix_create(1, 1)
            );
            P(result)
            E
            break;
        case EXPR_TENSOR_PRODUCT_N_TIMES: S
            result = matrix_tensor_product_n_times(left, (int)INDEX(right, 0, 0).real);
            P(result)
            E
            break;
        case EXPR_FIELD: 
            if(right == NULL) {
                result = left;
            }
            else {
                result = matrix_create(1, right->columns+1);
                for(unsigned int i = 1; i < result->columns; i++) {
                    INDEX(result, 0, i) = INDEX(right, 0, i-1);
                }
                INDEX(result, 0, 0) = INDEX(left, 0, 0);
            }
            break;
        case EXPR_REGISTER: 
            if(e->left->kind == EXPR_FIELD) left = matrix_transpose(left);
            if(right == NULL) result = left;
            else {
                result = matrix_tensor_product(
                    left, 
                    right
                );
            }
            break;
        case EXPR_MEASURE: {
            qm_result *m_result = NULL;
            if(e->right == NULL || regs->rows <= 2) {
                WHOLE_SYSTEM_MEASUREMENT_CODERUNNER:
                m_result = quantum_state_measure(regs);
                result = m_result->state;
            }
            else {
                unsigned int scope = (e->reg.end - e->reg.start + 1);
                const unsigned int qubits_count = log2(regs->rows);
                if(scope <= 0 || scope > qubits_count || e->reg.start > qubits_count) 
                    goto WHOLE_SYSTEM_MEASUREMENT_CODERUNNER;
                m_result = quantum_state_measure_subsystem(
                                           regs, 
                                           e->reg.start, 
                                           e->reg.end
                                      );
                result = m_result->state;
            }
            printf(CYN"Quantum state of the system after measurement: \n"GRN);
            matrix_print(result);
            printf(CYN"Classical bit representation: "GRN"%d \n"RESET, m_result->value);
            break;
        }
        case EXPR_APPLY_GATE: {
            left = expr_coderun(e->left, NULL);

            result = NULL;
            if(e->right != NULL) {
                const unsigned int qubits_count = log2(regs->rows);

                const unsigned int preceding_qubits_count = e->reg.start;
                const unsigned int measured_qubits_count = 
                    (e->reg.end - e->reg.start) + 1;
                const unsigned int proceeding_qubits_count = 
                    qubits_count - (e->reg.end + 1);

                if(preceding_qubits_count) result = 
                    quantum_gate_create(pow(2, preceding_qubits_count));

                if(result == NULL) result = left;
                else result = matrix_tensor_product(result, left);

                if(proceeding_qubits_count) result = 
                    matrix_tensor_product(result, 
                        quantum_gate_create(pow(2, proceeding_qubits_count))
                    );
            }
            else result = left;
            break;
        }
        case EXPR_AND: {
            left = expr_coderun(e->left, regs);
            quantum_state *new_regs = e->left->kind == EXPR_MEASURE || 
                (e->left->left && e->left->left->kind == EXPR_MEASURE) 
                ? left  
                : matrix_mul(left, regs);
            quantum_gate *concurrent_gate = expr_coderun(e->right, new_regs);
            if(concurrent_gate) result = concurrent_gate;
            else result = new_regs;
            break;
        }
        case EXPR_CIRCUIT_STEP: {
            left = expr_coderun(e->left, regs);
            quantum_state *new_regs = e->left->kind == EXPR_MEASURE || 
                (e->left->left && e->left->left->kind == EXPR_MEASURE) 
                ? left 
                : matrix_mul(left, regs);
            if(new_regs == NULL) new_regs = left;
            result = expr_coderun(e->right, new_regs);
            break;
        }
    }

    return result;
}

extern FILE *result_file;

extern unsigned short compile_time_calculations;

static char *var_create() {
    static unsigned int count = 0;
    char *result = (char *)smart_allocate(1 + log10(count) + 1, sizeof(char));
    sprintf(result, "t%u", count++);
    return result;
}
void decl_codegen(struct decl * const d) {
    if(!d) return;

    if(d->name) {
        if(!compile_time_calculations) expr_codegen(d->value, NULL);
        if(compile_time_calculations) {
            struct matrix *temp = expr_coderun(d->value, NULL);
            if(d->value->kind == EXPR_FIELD) temp = get_quantum_operator(temp, d->dimensions);
            d->operator = temp;
            fprintf(result_file, "quantum_gate *%s = quantum_gate_create(%d);\n", 
                                            d->name, 
                                            d->dimensions.rows);
            for(unsigned int i = 0; i < d->dimensions.rows; i++) {
                for(unsigned int j = 0; j < d->dimensions.columns; j++) {
                    fprintf(result_file, "INDEX(%s, %u, %u) = complex_create(%f, %f);\n", 
                                            d->name, 
                                            i, 
                                            j, 
                                            INDEX(d->operator, i, j).real, 
                                            INDEX(d->operator, i, j).imaginary);
                }
            }
        }
        else if(d->value->kind == EXPR_FIELD) {
            fprintf(result_file, "quantum_gate *%s = quantum_gate_create(%d);\n", 
                                            d->name, 
                                            d->dimensions.rows);
            struct expr *fields = d->value;
            for(unsigned int i = 0; i < d->dimensions.rows; i++) {
                for(unsigned int j = 0; j < d->dimensions.columns; j++) {
                    fprintf(result_file, "INDEX(%s, %u, %u) = INDEX(%s, 0, 0);\n", 
                                            d->name, 
                                            i, 
                                            j, 
                                            fields->name);
                    fields = fields->right;
                }
            }
        }
        else fprintf(result_file, "quantum_gate *%s = %s;\n", 
                                            d->name, 
                                            d->value->name);
    }
    else if(d->file_name) {
        decl_codegen(d->loaded);
    }
    else {
        if(compile_time_calculations) {
            quantum_state *registers = expr_coderun(d->value, NULL);
            d->value->name = var_create();
            fprintf(result_file, "quantum_state *%s = matrix_create_empty(%d, 1);\n", 
                                            d->value->name, 
                                            registers->rows);
            for(unsigned int i = 0; i < registers->rows; i++) {
                for(unsigned int j = 0; j < registers->columns; j++) {
                    fprintf(result_file, "INDEX(%s, %u, %u) = complex_create(%f, %f);\n", 
                                            d->value->name, 
                                            i, 
                                            j, 
                                            INDEX(registers, i, j).real, 
                                            INDEX(registers, i, j).imaginary);
                }
            }
        }
        else expr_codegen(d->value, NULL);
        expr_codegen(d->circuit, d->value);
    }

    decl_codegen(d->next);
}
void expr_codegen(struct expr * const e, struct expr * const regs) {
    if(!e) return;

    switch(e->kind) {
        case EXPR_NAME: break;
        case EXPR_COMPLEX_LITERAL: 
            e->name = var_create();
            fprintf(result_file, "struct matrix *%s = matrix_create_empty(1, 1);\n", 
                                        e->name);
            fprintf(result_file, "INDEX(%s, 0, 0) = complex_create(%f, %f);\n", 
                                        e->name, 
                                        e->complex_literal.real, 
                                        e->complex_literal.imaginary);
            break;
        case EXPR_KET ... EXPR_BRA: {
            char *temp = var_create();
            int dimension_index = e->kind == EXPR_KET 
                                    ? e->right->complex_literal.real 
                                    : e->left->complex_literal.real;
            int dimensions = e->kind == EXPR_KET 
                                    ? e->dimensions.rows 
                                    : e->dimensions.columns;
            fprintf(result_file, "qubit *%s = quantum_state_create(%d, %d);\n", 
                                        temp, 
                                        dimension_index, 
                                        dimensions);
            if(e->kind == EXPR_BRA) {
                e->name = var_create();
                fprintf(result_file, "quantum_state *%s = vector_get_dual(%s);\n", 
                                        e->name, 
                                        temp);
            }
            else e->name = temp;
            break;
        }
        case EXPR_SQRT: 
            expr_codegen(e->right, regs);
            e->name = e->right->name;
            fprintf(result_file, "INDEX(%s, 0, 0).real = sqrt(INDEX(%s, 0, 0).real);\n", 
                                        e->name, 
                                        e->name);
            break;
        case EXPR_MODULUS: 
        case EXPR_DIV: 
            expr_codegen(e->left, regs);
            expr_codegen(e->right, regs);
            e->name = var_create();
            char *operator = NULL;
            if(e->kind == EXPR_MODULUS) operator = "%%";
            else operator = "/";
            fprintf(result_file, "struct matrix *%s = matrix_create_empty(1, 1);\n", 
                                        e->name);
            fprintf(result_file, "INDEX(%s, 0, 0).real = INDEX(%s, 0, 0).real"
                                    " %s "
                                    "INDEX(%s, 0, 0).real;\n", 
                                        e->name, 
                                        e->left->name, 
                                        operator, 
                                        e->right->name);
            break;
        case EXPR_TENSOR_PRODUCT: 
        case EXPR_ADD ... EXPR_MUL: {
            expr_codegen(e->left, regs);
            expr_codegen(e->right, regs);
            e->name = var_create();
            char *function = NULL;
            if(e->kind == EXPR_ADD) function = "matrix_add";
            else if(e->kind == EXPR_SUB) function = "matrix_sub";
            else if(e->kind == EXPR_MUL) function = "matrix_mul";
            else if(e->kind == EXPR_TENSOR_PRODUCT) function = "matrix_tensor_product";
            fprintf(result_file, "struct matrix *%s = %s(%s, %s);\n", 
                                        e->name, 
                                        function, 
                                        e->left->name, 
                                        e->right->name);
            break;
        }
        case EXPR_POWER: 
            expr_codegen(e->left, regs);
            expr_codegen(e->right, regs);
            e->name = var_create();
            fprintf(result_file, "struct matrix *%s = matrix_create_empty(1, 1);\n", 
                                        e->name);
            fprintf(result_file, "INDEX(%s, 0, 0)"
                                 " = complex_pow(INDEX(%s, 0, 0), INDEX(%s, 0, 0));\n", 
                                        e->name, 
                                        e->left->name, 
                                        e->right->name);
            break;
        case EXPR_TENSOR_PRODUCT_N_TIMES: 
            expr_codegen(e->left, regs);
            expr_codegen(e->right, regs);
            e->name = var_create();
            fprintf(result_file, "struct matrix *%s"
                                 " = matrix_tensor_product_n_times"
                                        "(%s, INDEX(%s, 0, 0).real);\n", 
                                        e->name, 
                                        e->left->name, 
                                        e->right->name);
            break;
        case EXPR_FIELD: 
            expr_codegen(e->left, regs);
            e->name = e->left->name;
            expr_codegen(e->right, regs);
            break;
        case EXPR_REGISTER: {
            expr_codegen(e->left, regs);
            if(e->left->kind == EXPR_FIELD) {
                struct expr *temp = e->left;
                char *result_name = var_create();
                int reg_dimensions = temp->dimensions.columns;
                fprintf(result_file, "quantum_state *%s = matrix_create_empty(%d, 1);\n", 
                                        result_name, 
                                        temp->dimensions.columns);
                for(unsigned int i = 0; i < reg_dimensions; i++) {
                    fprintf(result_file, "INDEX(%s, %u, 0) = INDEX(%s, 0, 0);\n", 
                                        result_name, 
                                        i, 
                                        temp->name);
                    temp = temp->right;
                }
                e->left->name = result_name;
            }
            expr_codegen(e->right, regs);
            if(e->right != NULL) {
                e->name = var_create();
                fprintf(result_file, "quantum_state *%s = matrix_tensor_product(%s, %s);\n", 
                                        e->name, 
                                        e->left->name, 
                                        e->right->name);
            }
            else e->name = e->left->name;
            break;
        }
        case EXPR_MEASURE: 
            e->name = var_create();
            if(e->right == NULL) {
                WHOLE_SYSTEM_MEASUREMENT_CODEGENERATOR:
                fprintf(result_file, "qm_result *%s = quantum_state_measure(%s);\n", 
                                        e->name, 
                                        regs->name);
            }
            else {
                unsigned int scope = (e->reg.end - e->reg.start + 1);
                const unsigned int qubits_count = log2(regs->dimensions.rows);
                if(scope <= 0 || scope > qubits_count || e->reg.start > qubits_count) 
                    goto WHOLE_SYSTEM_MEASUREMENT_CODEGENERATOR;
                fprintf(result_file, "qm_result *%s "
                                    "= quantum_state_measure_subsystem(%s, %d, %d);\n", 
                                        e->name, 
                                        regs->name, 
                                        e->reg.start, 
                                        e->reg.end);
                // regs->dimensions.rows /= systems;
            }
            regs->name = var_create();
            fprintf(result_file, "quantum_state *%s = %s->state;\n", 
                                        regs->name, 
                                        e->name);
            fprintf(result_file, 
                "printf(CYN\"Quantum state of the system after measurement: \\n\"GRN);\n"
                "matrix_print(%s);\n"
                "printf(CYN\"Classical bit representation: \"GRN\"%%d \\n\"RESET, "
                                                                            "%s->value);\n", 
                                        regs->name, 
                                        e->name);
            break;
        case EXPR_RANGE: 
            expr_codegen(e->left, regs);
            expr_codegen(e->right, regs);
            break;
        case EXPR_APPLY_GATE: 
            expr_codegen(e->left, regs);
            if(e->right != NULL) {
                /* 

                   This is a version that will work even if in the future 
                   Q Assembly has support for runtime variable assignment.
                   For now, it just gives more flexibility an ease of use
                   in the generated C file with Q-SET instructions.

                */
                expr_codegen(e->right, regs);
                char *start_name = NULL;
                char *end_name = NULL;
                if(e->right->kind == EXPR_RANGE) {
                    start_name = e->right->left->name;
                    end_name = e->right->right->name;
                }
                else {
                    start_name = e->right->name;
                    end_name = e->right->name;
                }
                e->name = var_create();
                fprintf(result_file, 
                        "quantum_gate *%s = NULL;\n"

                        "{\n"
                        "const unsigned int qubits_count = log2(%s->rows);\n"

                        "const unsigned int preceding_qubits_count = INDEX(%s, 0, 0).real;\n"
                        "const unsigned int measured_qubits_count = \n"
                        "\t(INDEX(%s, 0, 0).real - INDEX(%s, 0, 0).real) + 1;\n"
                        "const unsigned int proceeding_qubits_count = \n"
                        "\tqubits_count - (INDEX(%s, 0, 0).real + 1);\n"

                        "if(preceding_qubits_count) %s = \n"
                        "\tquantum_gate_create(pow(2, preceding_qubits_count));\n"

                        "if(%s == NULL) %s = %s;\n"
                        "else %s = matrix_tensor_product(%s, %s);\n"

                        "if(proceeding_qubits_count) %s = \n"
                        "\tmatrix_tensor_product(%s, \n"
                        "\t\tquantum_gate_create(pow(2, proceeding_qubits_count))\n"
                        "\t);\n"
                        "}\n",          e->name, 
                                        regs->name, 
                                        start_name, 
                                        end_name, start_name, 
                                        end_name, 
                                        e->name, 
                                        e->name, e->name, e->left->name, 
                                        e->name, e->name, e->left->name, 
                                        e->name, 
                                        e->name);
            }
            else e->name = e->left->name;
            break;
        case EXPR_AND: 
        case EXPR_CIRCUIT_STEP: 
            expr_codegen(e->left, regs);
            if(e->left->kind == EXPR_APPLY_GATE) {
                char *old_regs_name = regs->name;
                regs->name = var_create();
                fprintf(result_file, "quantum_state *%s = matrix_mul(%s, %s);\n", 
                                        regs->name, 
                                        e->left->name, 
                                        old_regs_name);
            }
            // If e->left->kind == EXPR_MEASURE, then the reg->name field will already
            // be changed to the new register after the measurement.
            // That's why we don't need to check for this case.
            if(e->right) expr_codegen(e->right, regs);
            break;
    }
}