#include "object.h"

/******************************************************/
/*                     COMMON                         */
/******************************************************/

char *objtype_as_str(objtype type) {
    switch (type) {
        case Int:
            return "Int";
        case Float:
            return "Float";
        case Str:
            return "Str";
        case Bool:
            return "Bool";
        default:
            fprintf(stderr, "ERROR: '%d': Unrecognized object type", type);
            exit(EXIT_FAILURE);
    }
}

/******************************************************/
/*                       INT                          */
/******************************************************/

obj *new_int(long long value) {
    intobj *object = (intobj *)malloc(sizeof(intobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->type = Int;
    object->value = value;
    return (obj *)object;
}

/******************************************************/
/*                      FLOAT                         */
/******************************************************/

obj *new_float(double value) {
    floatobj *object = (floatobj *)malloc(sizeof(floatobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->type = Float;
    object->value = value;
    return (obj *)object;
}

/******************************************************/
/*                       STR                          */
/******************************************************/

#define STR_MIN_SIZE 15
obj *new_str(char *value) {
    strobj *object = (strobj *)malloc(sizeof(strobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->type = Str;
    size_t len = strlen(value);
    size_t cap = (len + 1 > STR_MIN_SIZE) ? len + 1 : STR_MIN_SIZE;
    char *string = (char *)malloc(cap);
    if (!string) {
        AllocError();
    }
    strcpy(string, value);
    object->chars = string;
    object->len = len;
    object->cap = cap;
    return (obj *)object;
}

/******************************************************/
/*                       BOOL                         */
/******************************************************/

obj *new_bool(bool value) {
    boolobj *object = (boolobj *)malloc(sizeof(boolobj));
    if (!object) {
        AllocError();
    }
    object->refcount = 1;
    object->type = Bool;
    object->value = value;
    return (obj *)object;
}

/******************************************************/
/*                     PRINTING                       */
/******************************************************/

void print(FILE *stream, obj *object) {
    switch (object->type) {
        case Int:
            fprintf(stream, "%lli", int_cast(object)->value);
            break;
        case Float:
            fprintf(stream, "%lf", float_cast(object)->value);
            break;
        case Str:
            fprintf(stream, "%s", str_cast(object)->chars);
            break;
        case Bool:
            if (bool_cast(object)->value) {
                fprintf(stream, "True");
            } else {
                fprintf(stream, "False");
            }
            break;
        default:
            fprintf(stderr, "ERROR: '%s': Unprintable object type", objtype_as_str(object->type));
            exit(EXIT_FAILURE);
    }
}

/******************************************************/
/*                  REPRESENTATION                    */
/******************************************************/

void print_repr(FILE *stream, obj *object) {
    switch (object->type) {
        case Int:
        case Float:
        case Bool:
            print(stream, object);
            break;
        case Str:
            fprintf(stream, "\"%s\"", str_cast(object)->chars);
            break;
        default:
            fprintf(stderr, "ERROR: '%s': Unrepresentable object type", objtype_as_str(object->type));
            exit(EXIT_FAILURE);
    }
}

/******************************************************/
/*                      COPYING                       */
/******************************************************/

obj *copy(obj *object) {
    switch (object->type) {
        case Int:
            return new_int(int_cast(object)->value);
        case Float:
            return new_float(float_cast(object)->value);
        case Str:
            return new_str(str_cast(object)->chars);
        case Bool:
            return new_bool(bool_cast(object)->value);
        default:
            fprintf(stderr, "ERROR: '%s': Uncopiable object type", objtype_as_str(object->type));
            exit(EXIT_FAILURE);
    }
}

/******************************************************/
/*                     DELETING                       */
/******************************************************/

void del(obj *object) {
    if (--object->refcount == 0) {
        switch (object->type) {
            case Int:
            case Float:
            case Bool:
                free(object);
                break;
            case Str:
                free(str_cast(object)->chars);
                free(object);
                break;
            default:
                fprintf(stderr, "ERROR: '%s': Undeletable object type", objtype_as_str(object->type));
                exit(EXIT_FAILURE);
        }
    }
}

/******************************************************/
/*                    TRUTHINESS                      */
/******************************************************/

bool istrue(obj *object) {
    switch (object->type) {
        case Int:
            return (bool)int_cast(object)->value;
        case Float:
            return (bool)float_cast(object)->value;
        case Str:
            return (bool)str_cast(object)->len;
        case Bool:
            return bool_cast(object)->value;
        default:
            fprintf(stderr, "ERROR: '%s': Type truthiness undefined", objtype_as_str(object->type));
            exit(EXIT_FAILURE);
    }
}

/******************************************************/
/*                     HASHING                        */
/******************************************************/

// size_t hash(obj *object) {
//     switch (object->type) {
//         default:
//             fprintf(stderr, "ERROR: '%s': Unhashable object type", objtype_as_str(object->type));
//             exit(EXIT_FAILURE);
//     }
// }