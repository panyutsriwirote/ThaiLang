#include "parser.h"
#include "ast.h"

typedef struct _seq {
    astseq *head;
    astseq *tail;
} seq;

static inline seq new_seq() {
    seq sequence;
    sequence.head = NULL;
    sequence.tail = NULL;
    return sequence;
}

static inline void append_seq(seq *sequence, ast *tree) {
    astseq *new_node = (astseq *)malloc(sizeof(astseq));
    if (!new_node) {
        AllocError();
    }
    new_node->tree = tree;
    new_node->next = NULL;
    if (sequence->head == NULL) {
        sequence->head = new_node;
        sequence->tail = new_node;
    } else {
        sequence->tail->next = new_node;
        sequence->tail = new_node;
    }
}