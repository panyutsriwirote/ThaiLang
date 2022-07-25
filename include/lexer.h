#ifndef LEXER_H
#define LEXER_H

typedef struct _toklist {
    int dummy;
} toklist;

toklist tokenize(char *text);

#endif