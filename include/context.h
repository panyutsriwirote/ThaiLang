#ifndef CONTEXT_H
#define CONTEXT_H

#include "hashtable.h"

typedef struct _ctx {
    tbl *local;
    struct _ctx *parent;
} ctx;

ctx *new_ctx(ctx *parent);
void set_value(ctx *context, char *name, obj *value);
obj *get_value(ctx *context, char *name);

static inline void free_ctx(ctx *context) {
    free_tbl(context->local);
    free(context);
}

#endif