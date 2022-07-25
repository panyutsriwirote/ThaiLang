#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "object.h"

typedef struct _entry {
    char *key;
    obj *value;
} entry;

typedef struct _tbl {
    entry *slot;
    size_t len;
    size_t cap;
} tbl;

#define DEFAULT_TABLE_INIT_SIZE 8

tbl *new_tbl(size_t init_size);
void insert_entry(tbl *t, char *key, obj *value);
obj *lookup(tbl *t, char *key);
void print_tbl(FILE *stream, tbl *t);
void print_debug_tbl(FILE *stream, tbl *t);

static inline void free_slot(tbl *t) {
    size_t cap = t->cap;
    for (size_t i = 0; i < cap; i++) {
        if (t->slot[i].key != NULL) {
            free(t->slot[i].key);
            del(t->slot[i].value);
        }
    }
    free(t->slot);
}

static inline void free_tbl(tbl *t) {
    free_slot(t);
    free(t);
}

#endif