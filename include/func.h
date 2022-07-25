#ifndef FUNC_H
#define FUNC_H

#include "ast.h"
#include "exec.h"

typedef struct _funcobj {
    common_fields
    astseq *argnames;
    astseq *body;
} funcobj;

#define func_cast(object) ((funcobj *)object)

#endif