#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
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
void decl_typecheck(struct decl * const d) {
    if(!d) return;

    struct dimensions dimensions = dimensions_create(0, 0);
    dimensions = expr_typecheck(d->value);
    expr_typecheck(d->circuit);
    if(d->name) d->dimensions = dimensions;

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
        case EXPR_NAME:  if(e->declaration) result = e->declaration->dimensions; break;
        case EXPR_COMPLEX_LITERAL: result = dimensions_create(1, 1); break;
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
    }

    e->dimensions = result;

    return result;
}