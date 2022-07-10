#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include <stdio.h>

/******************************************************/
/*                     COMMON                         */
/******************************************************/

typedef struct _obj obj;
typedef void (*printfunc)(FILE *, obj *);
typedef obj *(*copyfunc)(obj *);
typedef void (*delfunc)(void *);
typedef bool (*istruefunc)(obj *);

typedef enum _objtype {
    IntType, FloatType, StrType, BoolType
} objtype;

typedef struct _impl {
    objtype Type;
    char *TypeName;
    printfunc print;
    copyfunc copy;
    delfunc del;
    istruefunc istrue;
} impl;

#define common_fields\
    const impl *TypeImpl;\
    unsigned int refcount;

struct _obj {
    common_fields
};

static inline void refinc(obj *object) {
    object->refcount++;
}

static inline objtype type(obj *object) {
    return object->TypeImpl->Type;
}

static inline char *type_as_str(obj *object) {
    return object->TypeImpl->TypeName;
}

static inline void print(FILE *stream, obj *object) {
    object->TypeImpl->print(stream, object);
}

static inline obj *copy(obj *object) {
    return object->TypeImpl->copy(object);
}

static inline void del(obj *object) {
    if (--object->refcount == 0) {
        object->TypeImpl->del(object);
    }
}

static inline bool istrue(obj *object) {
    return object->TypeImpl->istrue(object);
}

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
    size_t used;
    size_t allocated;
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

#endif