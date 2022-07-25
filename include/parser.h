#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

astseq *parse(toklist *tokens);

#endif