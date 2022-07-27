#include <string.h>
#include "list.h"

#ifdef COUNT_MALLOC
#include "../../include/count-malloc/count-malloc.h"
#endif


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


SNode* SList_create(void* data, size_t data_size) {
  SNode* list = (SNode*)(malloc(sizeof(SNode)));
  if (list == NULL) return NULL;
  list->next = NULL;
  if (data == NULL || data_size == 0) {
    list->data = NULL;
  } else {
    list->data = malloc(data_size);
    if (list->data == NULL) {
      SList_free(list);
      return NULL;
    }
    memcpy(list->data, data, data_size);
  }
  return list;
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

SNode* SList_prepend(SNode* const list, void* data, size_t data_size) {
  SNode* node = SList_create(data, data_size);
  node->next = list;
  return node;
}


SNode* SList_get_item(SNode* list, size_t position) {
  SNode* node= list;
  size_t current_position = 0;
  while (current_position++ < position) {
    if (node == NULL || node->next == NULL) return NULL;
    node = node->next;
  }
  return node;
}

void* SList_get_data(SNode* list, size_t position) {
  SNode* node = SList_get_item(list, position);
  if (node == NULL) return NULL;
  return node->data;
}

SNode* SList_pop_left(SNode* list) {
  if (list == NULL) return NULL;
  SNode* head = list;
  list = list->next;
  head->next = NULL;
  SList_free(head);
  return list;
}


SNode* SList_pop_right(SNode* list) {
  if (list == NULL) return NULL;
  if (list->next == NULL) {
    SList_free(list);
    return NULL;
  }
  if (list->next->next == NULL) {
    SNode* tail = list->next;
    list->next = NULL;
    SList_free(tail);
    return list;
  }
  SList_pop_right(list->next);
  return list;
}
