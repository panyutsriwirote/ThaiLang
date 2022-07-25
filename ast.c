#include "ast.h"

char *asttype_as_str(asttype type) {
    switch (type) {
        case Const:
            return "Const";
        case Var:
            return "Var";
        case Call:
            return "Call";
        case Add:
            return "Add";
        case Sub:
            return "Sub";
        case Mult:
            return "Mult";
        case Div:
            return "Div";
        case Mod:
            return "Mod";
        case Exp:
            return "Exp";
        case Neg:
            return "Neg";
        case And:
            return "And";
        case Or:
            return "Or";
        case Not:
            return "Not";
        case VarDef:
            return "VarDef";
        case FuncDef:
            return "FuncDef";
        case Inc:
            return "Inc";
        case Dec:
            return "Dec";
        case Print:
            return "Print";
        case Return:
            return "Return";
        case Break:
            return "Break";
        case Continue:
            return "Continue";
        case For:
            return "For";
        case While:
            return "While";
        case If:
            return "If";
        default:
            fprintf(stderr, "ERROR: '%d': Unrecognized AST node type", type);
            exit(EXIT_FAILURE);
    }
}

static inline ast *new_tree() {
    ast *tree = (ast *)malloc(sizeof(ast));
    if (!tree) {
        AllocError();
    }
    return tree;
}

ast *Constant(obj *value) {
    ast *tree = new_tree();
    tree->type = Const;
    tree->branch.value = value;
    return tree;
}

ast *Variable(char *varname) {
    ast *tree = new_tree();
    tree->type = Var;
    tree->branch.varname = varname;
    return tree;
}

ast *FunctionCall(char *funcname, astseq *args) {
    ast *tree = new_tree();
    tree->type = Call;
    tree->branch.call.funcname = funcname;
    tree->branch.call.args = args;
    return tree;
}

ast *BinOp(asttype type, ast *left, ast *right) {
    ast *tree = new_tree();
    tree->type = type;
    tree->branch.binop.left = left;
    tree->branch.binop.right = right;
    return tree;
}

ast *UnOp(asttype type, ast *operand) {
    ast *tree = new_tree();
    tree->type = type;
    tree->branch.operand = operand;
    return tree;
}

ast *VariableDefinition(char *varname, ast *expr) {
    ast *tree = new_tree();
    tree->type = VarDef;
    tree->branch.vardef.varname = varname;
    tree->branch.vardef.expr = expr;
    return tree;
}

ast *FunctionDefinition(char *funcname, astseq *argnames, astseq *body) {
    ast *tree = new_tree();
    tree->type = FuncDef;
    tree->branch.funcdef.funcname = funcname;
    tree->branch.funcdef.argnames = argnames;
    tree->branch.funcdef.body = body;
    return tree;
}

ast *Crement(asttype type, char *varname) {
    ast *tree = new_tree();
    tree->type = type;
    tree->branch.varname = varname;
    return tree;
}

ast *ControlFlow(asttype type) {
    ast *tree = new_tree();
    tree->type = type;
    return tree;
}

ast *ForLoop(astseq *init_stmt, ast *expr, astseq *end_stmt, astseq *body) {
    ast *tree = new_tree();
    tree->type = For;
    tree->branch.for_loop.init_stmt = init_stmt;
    tree->branch.for_loop.expr = expr;
    tree->branch.for_loop.end_stmt = end_stmt;
    tree->branch.for_loop.body = body;
    return tree;
}

ast *WhileLoop(ast *expr, astseq *body) {
    ast *tree = new_tree();
    tree->type = While;
    tree->branch.while_loop.expr = expr;
    tree->branch.while_loop.body = body;
    return tree;
}

ast *IfBranch(ast *expr, astseq *body, astseq *alt) {
    ast *tree = new_tree();
    tree->type = If;
    tree->branch.if_branch.expr = expr;
    tree->branch.if_branch.body = body;
    tree->branch.if_branch.alt = alt;
    return tree;
}