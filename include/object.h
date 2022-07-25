#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/******************************************************/
/*                     COMMON                         */
/******************************************************/

static inline void AllocError() {
    fprintf(stderr, "ERROR: Failed to allocate memory");
    exit(EXIT_FAILURE);
}

typedef enum _objtype {
    Int, Float, Str, Bool, Func
} objtype;

char *objtype_as_str(objtype type);

#define common_fields\
    objtype type;\
    unsigned int refcount;

typedef struct _obj {
    common_fields
} obj;

static inline obj *ref(obj *object) {
    object->refcount++;
    return object;
}
void print(FILE *stream, obj *object);
void print_repr(FILE *stream, obj *object);
obj *copy(obj *object);
void del(obj *object);
bool istrue(obj *object);
// size_t hash(obj *object);

/******************************************************/
/*                TYPE DECLARATION                    */
/******************************************************/

typedef struct _intobj {
    common_fields
    long long value;
} intobj;

typedef struct _floatobj {
    common_fields
    double value;
} floatobj;

typedef struct _strobj {
    common_fields
    char *chars;
    size_t len;
    size_t cap;
} strobj;

typedef struct _boolobj {
    common_fields
    bool value;
} boolobj;

#define int_cast(object) ((intobj *)object)
#define float_cast(object) ((floatobj *)object)
#define str_cast(object) ((strobj *)object)
#define bool_cast(object) ((boolobj *)object)

obj *new_int(long long value);
obj *new_float(double value);
obj *new_str(char *value);
obj *new_bool(bool value);

static inline char *charcpy(char *string) {
    char *new_string = (char *)malloc(strlen(string) + 1);
    if (!new_string) {
        AllocError();
    }
    strcpy(new_string, string);
    return new_string;
}

#endif