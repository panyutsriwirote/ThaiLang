#include "eval.h"
#include "exec.h"
#include "func.h"

obj *eval(ast *tree, ctx *context) {
    obj *result;
    obj *left;
    obj *right;
    switch (tree->type) {
        case Const:
            result = tree->branch.value;
            break;
        case Var:
            result = get_value(context, tree->branch.varname);
            if (result == NULL) {
                fprintf(stderr, "ERROR: '%s': Undefined variable", tree->branch.varname);
                exit(EXIT_FAILURE);
            }
            break;
        case Call:
            left = get_value(context, tree->branch.call.funcname);
            if (left->type != Func) {
                fprintf(stderr, "ERROR: '%s': Trying to call non-function", tree->branch.call.funcname);
                exit(EXIT_FAILURE);
            }
            funcobj *function = func_cast(left);
            astseq *argname = function->argnames;
            astseq *arg = tree->branch.call.args;
            ctx *local_ctx = new_ctx(context);
            char *name;
            obj *value;
            while (argname != NULL && arg != NULL) {
                name = argname->tree->branch.varname;
                value = eval(arg->tree, context);
                insert_entry(local_ctx->local, name, value);
                argname = argname->next;
                arg = arg->next;
            }
            if (argname != NULL || arg != NULL) {
                fprintf(stderr, "ERROR: Incorrect number of argument(s)");
                exit(EXIT_FAILURE);
            }
            res out = exec(function->body, local_ctx);
            if (out.signal != ReturnSig) {
                fprintf(stderr, "ERROR: Function returns NULL");
                exit(EXIT_FAILURE);
            }
            result = out.object;
            break;
        case Add:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Sub:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Mult:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Div:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Mod:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Exp:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Pos:
            left = eval(tree->branch.operand, context);
            break;
        case Neg:
            left = eval(tree->branch.operand, context);
            break;
        case And:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Or:
            left = eval(tree->branch.binop.left, context);
            right = eval(tree->branch.binop.right, context);
            break;
        case Not:
            left = eval(tree->branch.operand, context);
            break;
        default:
            fprintf(stderr, "ERROR: '%s': Unevaluable AST node type", asttype_as_str(tree->type));
            exit(EXIT_FAILURE);
    }
    return result;
}