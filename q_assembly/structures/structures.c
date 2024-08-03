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