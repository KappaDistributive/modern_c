#include "utils/list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

SNode* test_creation() {
  SNode* list = {0};
  int x = -2;
  list = SList_create(&x, sizeof(int));
  x = 7;
  SList_append(list, &x, sizeof(x));
  x = -9;
  SList_append(list, &x, sizeof(x));

  return list;

}

int main() {
  SNode* list = test_creation();
  printf("printing list...\n");
  printf("Length: %zu\n", SList_length(list));
  while (list != NULL) {
    printf("%i\n", *(int*)list->data);
    list = list->next;
  }
}
