#ifndef EXEC_H
#define EXEC_H

#include "ast.h"
#include "context.h"

typedef enum _sig {
    NoSig, BreakSig, ContinueSig, ReturnSig
} sig;

typedef struct _res {
    sig signal;
    obj *object;
} res;

res exec(astseq *sequence, ctx *context);

#endif