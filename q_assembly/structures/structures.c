#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "smart_allocation.h"

unsigned int error_count;

struct decl *decl_create(char *name, 
                            struct expr *value, 
                            struct expr *circuit, 
                            struct decl *next) 
{
    struct decl *temp = (struct decl *)smart_allocate(1, sizeof(struct decl));
    temp->name = name;
    temp->value = value;
    temp->circuit = circuit;
    temp->next = next;
    return temp;
}

struct expr *expr_create(expr_t kind, 
                            struct expr *left, 
                            struct expr *right) 
{
    struct expr *temp = (struct expr *)smart_allocate(1, sizeof(struct expr));
    temp->kind = kind;
    temp->left = left;
    temp->right = right;
    return temp;
}

struct expr *expr_create_name(char *name) {
    struct expr *temp = expr_create(EXPR_NAME, NULL, NULL);
    temp->name = name;
    return temp;
}
struct expr *expr_create_complex_literal(struct complex num) {
    struct expr *temp = expr_create(EXPR_COMPLEX_LITERAL, NULL, NULL);
    temp->complex_literal = num;
    return temp;
}

void decl_print(const struct decl * const d) {
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

    decl_print(d->next);
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