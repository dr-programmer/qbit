#ifndef SCOPE_H
#define SCOPE_H

#include "structures.h"

struct hash_table {
    unsigned int size;
    unsigned int capacity;
    struct decl **declarations;
};

struct scope {
    struct hash_table *symbols;
    unsigned int depth;
    struct scope *next;
};

extern struct scope *symbol_table;

void scope_enter();
void scope_exit();
int scope_bind(struct decl *d);
struct decl *scope_lookup(const char * const name);
struct decl *scope_lookup_current(const char * const name);

#endif