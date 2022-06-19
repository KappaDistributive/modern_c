#pragma once
#include <stdlib.h>

struct SNode {
  void* data;
  struct SNode* next;
};

typedef struct SNode SNode;

SNode* SList_create(void* data, size_t data_size);

size_t SList_length(SNode const* const list);

SNode* SList_append(SNode* const list, void* data, size_t data_size);

SNode* SList_get_item(SNode const* const list, size_t position);
