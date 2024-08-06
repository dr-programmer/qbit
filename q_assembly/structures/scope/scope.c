#include "scope.h"
#define SMART_DEALLOCATION
#include "smart_allocation.h"

#include <string.h>

#define HASH_TABLE_DEFAULT_CAPACITY 16 // Must be a power of two

static struct hash_table *hash_table_create() {
    struct hash_table *temp = 
                (struct hash_table *)smart_allocate(1, sizeof(struct hash_table));
    temp->capacity = HASH_TABLE_DEFAULT_CAPACITY;
    temp->declarations = 
                (struct decl **)smart_allocate(temp->capacity, sizeof(struct decl *));
    return temp;
}
static struct scope *scope_create(unsigned int depth) {
    struct scope *temp = (struct scope *)smart_allocate(1, sizeof(struct scope));
    temp->symbols = hash_table_create();
    temp->depth = depth;
    return temp;
}

static int hash_table_free(const struct hash_table * const h) {
    if(!h) return 0;

    smart_free(h->declarations);
    smart_free(h);
    return 1;
}
static int scope_free(const struct scope * const s) {
    if(!s) return 0;

    hash_table_free(s->symbols);
    smart_free(s);
    return 1;
}

/* Implementing a djb2 algorithm with a minor change: 
            the return index is within the range of our hash table
            because of this expression: hash & (hashTable->capacity-1) */
static long hash_function(const char *name, const unsigned int capacity) {
    if(!name) return -1;

    unsigned long hash = 5381;
    int c;

    while (c = *name++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash & (capacity-1);
}

void scope_enter() {
    struct scope *temp = symbol_table;
    symbol_table = scope_create(temp->depth + 1);
    symbol_table->next = temp;
}
void scope_exit() {
    struct scope *temp = symbol_table;
    symbol_table = symbol_table->next;
    scope_free(temp);
}

static int hash_table_insert(struct hash_table * const h, const struct decl * const d) {
    if(!h || !d) return 1;

    if(h->size >= h->capacity * ((float)2/3)) {
        h->capacity *= 2;
        struct decl **temp = 
                    (struct decl **)smart_allocate(h->capacity, sizeof(struct decl *));
        memcpy(temp, h->declarations, h->size);
        smart_free(h->declarations);
        h->declarations = temp;
        if(h->declarations == NULL) return 2;
    }

    long index = hash_function(d->name, h->capacity);
    if(index == -1) return 3;

    for(; h->declarations[index] != NULL; index = (index + 1) % h->capacity);

    h->declarations[index] = (struct decl *)d;

    return 0;
}

int scope_bind(struct decl *d) {
    if(!d) return 0;

    return hash_table_insert(symbol_table->symbols, d);
}

struct decl *hash_table_find(const struct hash_table * const h, const char * const name) {
    if(!h || !name) return NULL;

    long index = hash_function(name, h->capacity);
    if(index == -1) return NULL;

    for(unsigned int safe = 0; strcmp(name, h->declarations[index]->name) != 0; 
                index = (index + 1) % h->capacity) 
    {
        if(safe >= h->capacity) return NULL;
        safe++;
    }

    return h->declarations[index];
}

struct decl *scope_lookup(const char * const name) {
    if(!name) return NULL;

    struct scope *current = symbol_table;
    while(current) {
        struct decl *temp = hash_table_find(current->symbols, name);
        if(temp != NULL) return temp;
        current = current->next;
    }

    return NULL;
}
struct decl *scope_lookup_current(const char * const name) {
    if(!name) return NULL;

    return hash_table_find(symbol_table->symbols, name);
}