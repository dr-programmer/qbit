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

struct dimensions {
    int rows;
    int columns;
};

struct decl {
    char *name;
    struct expr *value;
    struct expr *circuit;
    struct decl *next;

    struct dimensions dimensions;

    unsigned int line;
};

struct reg {
    int start;
    int end;
};

struct expr {
    expr_t kind;
    struct expr *left; 
    struct expr *right;

    char *name;
    struct complex complex_literal;

    struct decl *declaration;

    struct dimensions dimensions;
    struct reg reg;
    struct expr *reg_ptr;

    unsigned int line;
};

struct decl *decl_create(char *name, 
                            struct expr *value, 
                            struct expr *circuit, 
                            struct decl *next, 
                            unsigned int line);

struct expr *expr_create(expr_t kind, 
                            struct expr *left, 
                            struct expr *right, 
                            unsigned int line);

struct expr *expr_create_name(char *name, unsigned int line);
struct expr *expr_create_complex_literal(struct complex num, unsigned int line);

void decl_print(const struct decl * const d, const unsigned short is_error);
void expr_print(const struct expr * const e, const int tabs);

void printf_error(char *str, ...);

void decl_resolve(struct decl * const d);
void expr_resolve(struct expr * const e);

struct dimensions dimensions_create(int rows, int columns);
void decl_typecheck(struct decl * const d);
struct reg reg_create(int start, int end);
struct dimensions expr_typecheck(struct expr * const e, struct expr * const reg_ptr);

#endif