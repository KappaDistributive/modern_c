#include <string.h>
#include "list.h"

#ifdef COUNT_MALLOC
#include "../../include/count-malloc/count-malloc.h"
#endif


SNode* SList_create(void* data, size_t data_size) {
  SNode* list = (SNode*)(malloc(sizeof(SNode)));
  if (list == NULL) return NULL;
  if (data != NULL && data_size > 0) {
    list->data = malloc(data_size);
    if (list->data == NULL) {
      free(list);
      return NULL;
    }
    memcpy(list->data, data, data_size);
  }
  return list;
}


void SList_free(SNode* list) {
  if (list->next != NULL) {
    SList_free(list->next);
  }
  if (list != NULL && list->data != NULL) {
    free(list->data);
  }
  if (list != NULL) {
    free(list);
  }
}

size_t SList_length(SNode const* const list) {
  if(list == NULL) return 0;
  return 1 + SList_length(list->next);
}

SNode* SList_append(SNode* const list, void* data, size_t data_size) {
  if (list == NULL) {
    return NULL;
  }
  SNode* node = list;
  while(node->next != NULL) {
    node = node->next;
  }
  SNode* new_node = SList_create(data, data_size);
  node->next = new_node;

  return new_node;
}

SNode* SList_get_item(SNode const* const list, size_t position) {
  SNode* node = (SNode*)malloc(sizeof(SNode));
  if (node == NULL) return NULL;
  memcpy(node, list, sizeof(SNode));
  size_t current_position = 0;
  while (current_position++ < position && node->next != NULL) {
    node = node->next;
  }
  if (current_position == position) {
    return node;
  }
  return NULL;
}

