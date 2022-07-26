#include <stdio.h>

#include "utils/list.h"

int main() {
  printf("This is challenge 7\n");
  SNode* list = SList_create(NULL, 0);
  printf("%zu\n", SList_length(list));
  SList_free(list);
}
