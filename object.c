#include "object.h"
#include <stdlib.h>
#include <string.h>

#define declare_func(type)\
    void print_##type(FILE *stream, obj *object);\
    obj *copy_##type(obj *object);\
    void del_##type(void *object);\
    bool istrue_##type(obj *object);

void AllocError() {
    fprintf(stderr, "ERROR: Failed to allocate memory");
    exit(EXIT_FAILURE);
}

/******************************************************/
/*                       INT                          */
/******************************************************/

declare_func(int)

static const impl INT = {
    .Type = IntType,
    .TypeName = "INT",
    .print = print_int,
    .copy = copy_int,
    .del = free,
    .istrue = istrue_int
};

obj *new_int(long long value) {
    intobj *object = (intobj *)malloc(sizeof(intobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->TypeImpl = &INT;
    object->value = value;
    return (obj *)object;
}

void print_int(FILE *stream, obj *object) {
    fprintf(stream, "%lli", int_cast(object)->value);
}

obj *copy_int(obj *object) {
    return new_int(int_cast(object)->value);
}

bool istrue_int(obj *object) {
    return (bool)int_cast(object)->value;
}

/******************************************************/
/*                      FLOAT                         */
/******************************************************/

declare_func(float)

static const impl FLOAT = {
    .Type = FloatType,
    .TypeName = "FLOAT",
    .print = print_float,
    .copy = copy_float,
    .del = free,
    .istrue = istrue_float
};

obj *new_float(double value) {
    floatobj *object = (floatobj *)malloc(sizeof(floatobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->TypeImpl = &FLOAT;
    object->value = value;
    return (obj *)object;
}

void print_float(FILE *stream, obj *object) {
    fprintf(stream, "%lf", float_cast(object)->value);
}

obj *copy_float(obj *object) {
    return new_float(float_cast(object)->value);
}

bool istrue_float(obj *object) {
    return (bool)float_cast(object)->value;
}

/******************************************************/
/*                       STR                          */
/******************************************************/

declare_func(str)

static const impl STR = {
    .Type = StrType,
    .TypeName = "STR",
    .print = print_str,
    .copy = copy_str,
    .del = del_str,
    .istrue = istrue_str
};

obj *new_str(char *value) {
    strobj *object = (strobj *)malloc(sizeof(strobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->TypeImpl = &STR;
    size_t used = strlen(value) + 1;
    size_t allocated = used + 10;
    char *string = (char *)malloc(allocated);
    if (!string) {
        AllocError();
    }
    strcpy(string, value);
    object->chars = string;
    object->used = used;
    object->allocated = allocated;
    return (obj *)object;
}

void print_str(FILE *stream, obj *object) {
    fprintf(stream, "%s", str_cast(object)->chars);
}

obj *copy_str(obj *object) {
    strobj *old_object = str_cast(object);
    strobj *new_object = (strobj *)malloc(sizeof(strobj));
    if (!object) {
        AllocError();
    }
    new_object->refcount = 1;
    new_object->TypeImpl = &STR;
    char *new_string = (char *)malloc(old_object->allocated);
    if (!new_string) {
        AllocError();
    }
    strcpy(new_string, old_object->chars);
    new_object->chars = new_string;
    new_object->used = old_object->used;
    new_object->allocated = old_object->allocated;
    return (obj *)new_object;
}

void del_str(void *object) {
    free(str_cast(object)->chars);
    free(object);
}

bool istrue_str(obj *object) {
    return str_cast(object)->chars[0] == '\0' ? false : true;
}

/******************************************************/
/*                       BOOL                         */
/******************************************************/

declare_func(bool)

static const impl BOOL = {
    .Type = BoolType,
    .TypeName = "BOOL",
    .print = print_bool,
    .copy = copy_bool,
    .del = free,
    .istrue = istrue_bool
};

obj *new_bool(bool value) {
    boolobj *object = (boolobj *)malloc(sizeof(boolobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->TypeImpl = &BOOL;
    object->value = value;
    return (obj *)object;
}

void print_bool(FILE *stream, obj *object) {
    if (bool_cast(object)->value) {
        fprintf(stream, "True");
    } else {
        fprintf(stream, "False");
    }
}

obj *copy_bool(obj *object) {
    return new_bool(bool_cast(object)->value);
}

bool istrue_bool(obj *object) {
    return bool_cast(object)->value;
}