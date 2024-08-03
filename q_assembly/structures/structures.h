#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "complex_numbers.h"

extern unsigned int error_count;

typedef enum {
    EXPR_MEASURE, 
    EXPR_APPLY_GATE, 
    EXPR_RANGE, 

    EXPR_CIRCUIT_STEP, 
    EXPR_FIELD, 
    EXPR_REGISTER, 

    EXPR_AND, 

    EXPR_ADD, 
    EXPR_SUB, 
    EXPR_MUL, 
    EXPR_DIV, 
    EXPR_MODULUS, 
    EXPR_TENSOR_PRODUCT, 

    EXPR_SQRT, 

    EXPR_KET, 
    EXPR_BRA, 

    EXPR_NAME, 
    EXPR_COMPLEX_LITERAL
} expr_t;

struct decl {
    char *name;
    struct expr *value;
    struct expr *circuit;
    struct decl *next;
};

struct expr {
    expr_t kind;
    struct expr *left; 
    struct expr *right;

    char *name;
    struct complex complex_literal;
};

struct decl *decl_create(char *name, 
                            struct expr *value, 
                            struct expr *circuit, 
                            struct decl *next);

struct expr *expr_create(expr_t kind, 
                            struct expr *left, 
                            struct expr *right);

struct expr *expr_create_name(char *name);
struct expr *expr_create_complex_literal(struct complex num);

#endif