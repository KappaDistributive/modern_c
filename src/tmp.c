#include "./utils/list.h"
#include <stdio.h>

int main() {
  printf("Hello, world!\n");
  int x = 5;
  SNode *list = SList_create(&x, sizeof(int));
  SList_free(list);
}