#include "hashtable.h"

tbl *new_tbl(size_t init_size) {
    tbl *new_t = (tbl *)malloc(sizeof(tbl));
    if (!new_t) {
        AllocError();
    }
    new_t->slot = (entry *)malloc(sizeof(entry) * init_size);
    if (!new_t->slot) {
        AllocError();
    }
    for (size_t i = 0; i < init_size; i++) {
        new_t->slot[i].key = NULL;
    }
    new_t->len = 0;
    new_t->cap = init_size;
    return new_t;
}

static inline size_t hash(char *key) {
    size_t len = strlen(key);
    unsigned char *p = (unsigned char *)key;
    size_t HASH = *p << 7;
    while (len-- > 0) {
        HASH = (1000003*HASH) ^ *p++;
    }
    HASH ^= strlen(key);
    return HASH;
}

static inline void rehash(tbl *source, tbl *destination) {
    size_t cap = source->cap;
    for (size_t i = 0; i < cap; i++) {
        if (source->slot[i].key == NULL) {
            continue;
        }
        insert_entry(destination, source->slot[i].key, source->slot[i].value);
    }
}

static inline void resize_tbl(tbl *t) {
    tbl *temp = new_tbl(t->cap * 2);
    rehash(t, temp);
    free_slot(t);
    t->slot = temp->slot;
    t->cap *= 2;
    free(temp);
}

void insert_entry(tbl *t, char *key, obj *value) {
    if (t->len >= (2.0/3.0) * t->cap) {
        resize_tbl(t);
    }
    size_t cap = t->cap;
    size_t i;
    for (i = hash(key) % cap;
        t->slot[i].key != NULL;
        i = ((i * 5) + 1) % cap)
    {
        if (strcmp(t->slot[i].key, key) == 0) {
            free(t->slot[i].key);
            del(t->slot[i].value);
            t->slot[i].value = value;
            return;
        }
    }
    t->len++;
    t->slot[i].key = charcpy(key);
    t->slot[i].value = ref(value);
}

obj *lookup(tbl *t, char *key) {
    size_t cap = t->cap;
    size_t i = hash(key) % cap;
    for (char *cur_key = t->slot[i].key;
        cur_key != NULL;
        cur_key = t->slot[i].key) 
    {
        if (strcmp(cur_key, key) == 0) {
            return t->slot[i].value;
        }
        i = ((5 * i) + 1) % cap;
    }
    return NULL;
}

void print_tbl(FILE *stream, tbl *t) {
    fprintf(stream, "{");
    size_t cap = t->cap;
    char *cur_key;
    size_t i;
    for (i = 0; i < cap; i++) {
        cur_key = t->slot[i].key;
        if (cur_key == NULL) {
            continue;
        }
        fprintf(stream, "%s:", cur_key);
        print_repr(stream, t->slot[i].value);
        i++;
        break;
    }
    for (; i < cap; i++) {
        cur_key = t->slot[i].key;
        if (cur_key == NULL) {
            continue;
        }
        fprintf(stream, ", %s:", cur_key);
        print_repr(stream, t->slot[i].value);
    }
    fprintf(stream, "}");
}

void print_debug_tbl(FILE *stream, tbl *t) {
    fprintf(stream, "{\n");
    size_t cap = t->cap;
    char *cur_key;
    size_t i;
    for (i = 0; i < cap; i++) {
        cur_key = t->slot[i].key;
        if (cur_key == NULL) {
            fprintf(stream, "%d\tNULL\n", i);
            continue;
        }
        fprintf(stream, "%d\t%s:", i, cur_key);
        print_repr(stream, t->slot[i].value);
        fprintf(stream, "\n");
    }
    fprintf(stream, "}");
}