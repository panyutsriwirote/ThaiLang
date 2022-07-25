#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
#include "context.h"

obj *eval(ast *tree, ctx *context);

#endif