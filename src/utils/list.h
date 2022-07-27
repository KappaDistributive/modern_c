#pragma once
#include <stdlib.h>

struct SNode {
  void* data;
  struct SNode* next;
};


typedef struct SNode SNode;

SNode* SList_create(void* data, size_t data_size);

void SList_free(SNode* list);

size_t SList_length(SNode const* const list);

SNode* SList_append(SNode* const list, void* data, size_t data_size);

SNode* SList_prepend(SNode* const list, void* data, size_t data_size);

SNode* SList_get_item(SNode* list, size_t position);

void* SList_get_data(SNode* list, size_t position);

SNode* SList_pop_left(SNode* list);

SNode* SList_pop_right(SNode* list);
