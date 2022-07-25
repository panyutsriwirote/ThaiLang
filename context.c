#include "context.h"

ctx *new_ctx(ctx *parent) {
    ctx *context = (ctx *)malloc(sizeof(ctx));
    if (!context) {
        AllocError();
    }
    context->local = new_tbl(DEFAULT_TABLE_INIT_SIZE);
    context->parent = parent;
    return context;
}

void set_value(ctx *context, char *name, obj *value) {
    obj *object;
    do {
        object = lookup(context->local, name);
        if (object != NULL) {
            insert_entry(context->local, name, value);
            return;
        }
        context = context->parent;
    } while (context != NULL);
    insert_entry(context->local, name, value);
}

obj *get_value(ctx *context, char *name) {
    obj *object;
    do {
        object = lookup(context->local, name);
        if (object != NULL) {
            return object;
        }
        context = context->parent;
    } while (context != NULL);
    return NULL;
}