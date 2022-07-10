#include <stdio.h>
#include <stdlib.h>
#include "object.h"

void println(obj *object) {
    print(stdout, object);
    printf("\n");
}

int main(int argc, char **argv) {
    obj *intob = new_int(0);
    obj *floatob = new_float(0.0);
    obj *strob = new_str("");
    obj *boolob = new_bool(false);
    println(intob);
    println(floatob);
    println(strob);
    println(boolob);
    if (istrue(intob)) {
        printf("int is true\n");
    } else {
        printf("int is false\n");
    }
     if (istrue(floatob)) {
        printf("float is true\n");
    } else {
        printf("float is false\n");
    }
     if (istrue(strob)) {
        printf("str is true\n");
    } else {
        printf("str is false\n");
    }
     if (istrue(boolob)) {
        printf("bool is true\n");
    } else {
        printf("bool is false\n");
    }
    obj *intcopy = copy(intob);
    obj *floatcopy = copy(floatob);
    obj *strcopy = copy(strob);
    obj *boolcopy = copy(boolob);
    del(intob);
    del(floatob);
    del(strob);
    del(boolob);
    println(intcopy);
    println(floatcopy);
    println(strcopy);
    println(boolcopy);
    del(intcopy);
    del(floatcopy);
    del(strcopy);
    del(boolcopy);
    return EXIT_SUCCESS;
}