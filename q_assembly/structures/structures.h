#ifndef STRUCTURES_H
#define STRUCTURES_H

extern unsigned int error_count;

struct decl {
    char *name;
    struct decl *next;
};

struct decl *decl_create();

#endif