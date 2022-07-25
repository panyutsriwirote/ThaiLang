#ifndef AST_H
#define AST_H

#include "object.h"

typedef enum _asttype {
    // Expression
    Const, Var, Call, Add, Sub, Mult, Div, Mod, Exp, Pos, Neg, And, Or, Not,
    // Statement
    VarDef, FuncDef, Inc, Dec, Print, Return, Break, Continue, For, While, If
} asttype;

char *asttype_as_str(asttype type);

typedef struct _ast {
    asttype type;
    union {
        obj *value;
        char *varname;
        struct {
            char *funcname;
            struct _astseq *args;
        } call;
        struct {
            struct _ast *left;
            struct _ast *right;
        } binop;
        struct _ast *operand;
        struct {
            char *varname;
            struct _ast *expr;
        } vardef;
        struct {
            char *funcname;
            struct _astseq *argnames;
            struct _astseq *body;
        } funcdef;
        struct {
            struct _ast *expr;
            struct _astseq *body;
            struct _astseq *alt;
        } if_branch;
        struct {
            struct _ast *expr;
            struct _astseq *body;
        } while_loop;
        struct {
            struct _astseq *init_stmt;
            struct _ast *expr;
            struct _astseq *end_stmt;
            struct _astseq *body;
        } for_loop;
    } branch;
} ast;

typedef struct _astseq {
    ast *tree;
    struct _astseq *next;
} astseq;

ast *Constant(obj *value);
ast *Variable(char *varname);
ast *FunctionCall(char *funcname, astseq *args);
ast *BinOp(asttype type, ast *left, ast *right);
ast *UnOp(asttype type, ast *operand);
ast *VariableDefinition(char *varname, ast *expr);
ast *FunctionDefinition(char *funcname, astseq *argnames, astseq *body);
ast *Crement(asttype type, char *varname);
ast *ControlFlow(asttype type);
ast *ForLoop(astseq *init_stmt, ast *expr, astseq *end_stmt, astseq *body);
ast *WhileLoop(ast *expr, astseq *body);
ast *IfBranch(ast *expr, astseq *body, astseq *alt);

#endif