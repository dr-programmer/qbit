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
        case EXPR_AND: expr_print(e->left, 0); 
                            if(e->right) {
                                printf(" && ");
                                expr_print(e->right, 0);
                            }
                            break;
        case EXPR_FIELD: expr_print(e->left, 0); 
                            if(e->right) {
                                int next_tabs = 0;
                                if(tabs == -1) {
                                    printf(" | ");
                                    next_tabs = -1;
                                }
                                else printf(", ");
                                expr_print(e->right, next_tabs);
                            }
                            break;
        case EXPR_REGISTER: printf("{"); 
                            expr_print(e->left, -1);
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

void decl_resolve(struct decl * const d) {
    if(!d) return;

    if(d->name) {
        if(scope_lookup_current(d->name)) 
            printf_error(RED"Error "MAG"|%s|"RESET"->"YEL"\n|%D|"RESET" on line %d \n", 
                            "variable already exists", d, d->line);
        else scope_bind(d);
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
            printf_error(RED"Error "MAG"|%s|"RESET"\n\t->"YEL"|%E|"RESET" on line %d \n", 
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
                printf_error(RED"Error "MAG 
                    "|cannot create a 2D quantum state from the value "BLU"(%d)"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    qubit_value, e, e->line);
            
            if(e->kind == EXPR_KET) result = dimensions_create(2, 1);
            else result = dimensions_create(1, 2);
            break;
        }
        case EXPR_SQRT: 
        case EXPR_MODULUS: 
            if(e->left && (left.rows != 1 || left.columns != 1 
                || right.rows != 1 || right.columns != 1)) 
                printf_error(RED"Error "MAG 
                    "|cannot apply binary real operator "BLU"(%%)"
                    MAG" between operands of dimension"BLU 
                    " [%dx%d]"MAG" and "BLU"[%dx%d]"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    left.rows, left.columns, right.rows, right.columns, e, e->line);
            else if(right.rows != 1 || right.columns != 1) 
                printf_error(RED"Error "MAG 
                    "|cannot apply unitary complex operator "BLU"(#)"
                    MAG" on operand of dimension"BLU 
                    " [%dx%d]"MAG"|"RESET"\n\t->"YEL"|%E|"RESET" on line %d \n", 
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
                        ? ((left.rows <= 1 || left.columns <= 1) 
                            || (right.rows <= 1 || right.columns <= 1)) 
                        : 1;
            if(add_sub_check && mul_check && div_check && tensor_check) 
                printf_error(RED"Error "MAG 
                    "|cannot apply binary operator "BLU"(%c)"MAG
                    " between operands of dimension"BLU 
                    " [%dx%d]"MAG" and "BLU"[%dx%d]"MAG"|"RESET 
                    "\n\t->"YEL"|%E|"RESET" on line %d \n", 
                    operator, left.rows, left.columns, right.rows, right.columns, e, e->line);
            
            if(e->kind == EXPR_TENSOR_PRODUCT) {
                result.rows = left.rows * right.rows;
                result.columns = left.columns * right.columns;
            }
            else {
                result.rows = left.rows;
                result.columns = right.columns;
            }
            break;
        }
        case EXPR_RANGE: 
            e->reg = reg_create(
                e->left->complex_literal.real, 
                e->right->complex_literal.real
            );
            break;
        case EXPR_APPLY_GATE: if(e->right) e->reg = e->right->reg; break;
        case EXPR_MEASURE: if(e->right) e->reg = e->right->reg; break;
        case EXPR_FIELD: result = dimensions_create(0, right.columns + 1); break;
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
            result->fields[i][j] = m->fields[0][j + i * d.columns];
        }
    }

    return result;
}
void decl_coderun(struct decl * const d) {
    if(!d) return;

    if(d->name == NULL) {
        quantum_state *registers = expr_coderun(d->value, NULL);
        expr_coderun(d->circuit, registers);
    }
    else {
        struct matrix *temp = expr_coderun(d->value, NULL);
        if(d->value->kind == EXPR_FIELD) temp = get_quantum_operator(temp, d->dimensions);
        d->operator = temp;
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
            P(result) P(result->fields) P(result->fields[0])
            E
            break;
        case EXPR_KET: 
            result = quantum_state_create(right->fields[0][0].real, e->dimensions.rows);
            break;
        case EXPR_BRA: {
            quantum_state *temp = 
                quantum_state_create(left->fields[0][0].real, e->dimensions.columns);
            result = vector_get_dual(temp);
            break;
        }
        case EXPR_SQRT: 
            right->fields[0][0].real = sqrt(right->fields[0][0].real);
            result = right;
            break;
        case EXPR_MODULUS: 
            result = matrix_mul_scalar(
                complex_create(
                    (int)left->fields[0][0].real % (int)right->fields[0][0].real, 
                    0
                ), 
                matrix_create(1, 1)
            );
            break;
        case EXPR_ADD: 
            result = matrix_add(left, right);
            break;
        case EXPR_SUB: 
            result = matrix_sub(left, right);
            break;
        case EXPR_MUL: 
            result = matrix_mul(left, right);
            break;
        case EXPR_DIV: 
            result = matrix_mul_scalar(
                complex_div(left->fields[0][0], right->fields[0][0]), 
                matrix_create(1, 1)
            );
            break;
        case EXPR_TENSOR_PRODUCT: 
            result = matrix_tensor_product(left, right);
            break;
        case EXPR_FIELD: 
            if(right == NULL) {
                result = left;
            }
            else {
                result = matrix_create(1, right->columns+1);
                for(unsigned int i = 1; i < result->columns; i++) {
                    result->fields[0][i] = right->fields[0][i-1];
                }
                result->fields[0][0] = left->fields[0][0];
            }
            break;
        case EXPR_REGISTER: 
            if(right == NULL) result = matrix_transpose(left);
            else {
                result = matrix_tensor_product(
                    matrix_transpose(left), 
                    right
                );
            }
            break;
        case EXPR_MEASURE: {
            qm_result *m_result = NULL;
            if(e->right == NULL || regs->rows <= 2) {
                WHOLE_SYSTEM_MEASUREMENT:
                m_result = quantum_state_measure(regs);
                result = m_result->state;
            }
            else {
                unsigned int scope = (e->reg.end - e->reg.start + 1);
                unsigned int systems = regs->rows / 2 / scope;
                if(systems == 1) goto WHOLE_SYSTEM_MEASUREMENT;
                unsigned int system_index;
                if(scope - 1 + e->reg.start == 0) system_index = 0;
                else system_index = systems / (scope - 1 + e->reg.start);
                m_result = quantum_state_measure_subsystem(
                                           regs, 
                                           system_index, 
                                           systems
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
                for(unsigned int i = 0; i < regs->rows;) {
                    if(i < e->reg.start * 2 || i > e->reg.end * 2) {
                        if(!result) result = quantum_gate_create(2);
                        else result = matrix_tensor_product(result, quantum_gate_create(2));
                        i+=2;
                    }
                    else if(i <= e->reg.end * 2) {
                        if(!result) result = left;
                        else result = matrix_tensor_product(result, left);
                        i += (e->reg.end+1) * 2;
                    }
                }
            }
            else result = left;
            break;
        }
        case EXPR_AND: {
            left = expr_coderun(e->left, regs);
            quantum_state *new_regs = matrix_mul(left, regs);
            quantum_gate *concurrent_gate = expr_coderun(e->right, new_regs);
            if(concurrent_gate) result = concurrent_gate;
            else if(new_regs) result = new_regs;
            else result = left;
            break;
        }
        case EXPR_CIRCUIT_STEP: {
            left = expr_coderun(e->left, regs);
            quantum_state *new_regs = matrix_mul(left, regs);
            if(new_regs == NULL) new_regs = left;
            result = expr_coderun(e->right, new_regs);
            break;
        }
    }

    return result;
}