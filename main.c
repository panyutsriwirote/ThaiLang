#include "hashtable.h"

int main(int argc, char **argv) {
    tbl *test = new_tbl(DEFAULT_TABLE_INIT_SIZE);
    print_tbl(stdout, test);
    obj *INT1 = new_int(1);
    obj *INT2 = new_int(2);
    obj *INT3 = new_int(3);
    obj *INT4 = new_int(4);
    obj *INT5 = new_int(5);
    obj *INT6 = new_int(6);
    obj *INT7 = new_int(7);
    obj *INT8 = new_int(8);
    obj *STR = new_str("test_string");
    insert_entry(test, "1", INT1);
    insert_entry(test, "2", INT2);
    insert_entry(test, "3", INT3);
    insert_entry(test, "4", INT4);
    insert_entry(test, "5", INT5);
    insert_entry(test, "6", INT6);
    insert_entry(test, "7", INT7);
    insert_entry(test, "8", INT8);
    insert_entry(test, "STR", STR);
    print_debug_tbl(stdout, test);
    printf("\n");
    print(stdout, lookup(test, "STR"));
    print(stdout, lookup(test, "5"));
    free_tbl(test);
    del(INT1);
    del(INT2);
    del(INT3);
    del(INT4);
    del(INT5);
    del(INT6);
    del(INT7);
    del(INT8);
    del(STR);
    return EXIT_SUCCESS;
}