#include "exec.h"
#include "eval.h"
#include "func.h"

res exec(astseq *sequence, ctx *context) {
    ast *tree;
    obj *object;
    while (sequence != NULL) {
        tree = sequence->tree;
        switch (tree->type) {
            case VarDef:
                break;
            case FuncDef:
                break;
            case Inc:
                break;
            case Dec:
                break;
            case Print:
                break;
            case Return:
                break;
            case Break:
                break;
            case Continue:
                break;
            case For:
                break;
            case While:
                break;
            case If:
                break;
            case Call:
                object = get_value(context, tree->branch.call.funcname);
                if (object->type != Func) {
                    fprintf(stderr, "ERROR: '%s': Trying to call non-function", tree->branch.call.funcname);
                    exit(EXIT_FAILURE);
                }
                funcobj *function = func_cast(object);
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
                if (out.signal == ReturnSig) {
                    del(out.object);
                }
                break;
            default:
                fprintf(stderr, "ERROR '%s': Unexecutable AST node type", asttype_as_str(tree->type));
                exit(EXIT_FAILURE);
        }
        sequence = sequence->next;
    }
}