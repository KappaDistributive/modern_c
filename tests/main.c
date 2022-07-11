#include "../include/minunit.h"
#include "../src/utils/list.h"
#include <stdio.h>

int tests_run = 0;
int foo = 7;

static char* test_list_creation() {
    int x = 5;
    SNode* list = SList_create(&x, sizeof(int));
    mu_assert("list != NULL", list!= NULL);
    mu_assert("*(int*)list->data == 5", *(int*)list->data == 5);
    mu_assert("list->next == NULL", list->next == NULL);

    SList_free(list);

    return 0;
}

static char* test_list_length() {
    mu_assert("SList_length(NULL) == 0", SList_length(NULL) == 0);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_list_creation);
    mu_run_test(test_list_length);

     return 0;
 }

int main(int argc, char **argv) {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }

