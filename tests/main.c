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
    int x = 5;
    SNode* list = SList_create(&x, sizeof(int));
    mu_assert("SList_length(list) == 1", SList_length(list) == 1);
    x = 2;
    SList_append(list, &x, sizeof(int));
    mu_assert("SList_length(list) == 2", SList_length(list) == 2);
    x = 1;
    SList_append(list, &x, sizeof(int));
    mu_assert("SList_length(list) == 2", SList_length(list) == 3);

    SList_free(list);

    return 0;
}

static char* test_get_item() {
    int x = 1;
    SNode* list = SList_create(&x, sizeof(int));
    for (x = 2; x < 10; ++x)
        SList_append(list, &x, sizeof(int));

    for (size_t index = 0; index < SList_length(list); ++index)  {
        SNode* node = SList_get_item(list, index);
        mu_assert("node != NULL", node != NULL);
        mu_assert("node->data != NULL", node->data != NULL);
        // printf("index: %zu, value: %d\n", index, *(int*)node->data);
        mu_assert("*(int*)node->data has incorrect value.", *(int*)node->data == (int)(index + 1));
    }

    for (size_t index = 0; index < SList_length(list); ++index)  {
        SNode* node = SList_get_item(list, SList_length(list) + index);
        mu_assert("node == NULL", node == NULL);
    }

    SList_free(list);

    return 0;
}

static char* all_tests() {
    mu_run_test(test_list_creation);
    mu_run_test(test_list_length);
    mu_run_test(test_get_item);

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

