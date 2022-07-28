#include <stdbool.h>
#include <stdio.h>

#include "utils/list.h"

bool is_connected(size_t num_vertices,
                  const bool graph[num_vertices][num_vertices], int source,
                  int destination) {
  if (source < 0 || destination < 0 || source >= (int)num_vertices ||
      destination >= (int)num_vertices) {
    return false;
  }
  return graph[source][destination];
}

SNode *breadth_first_search(size_t num_vertices,
                            const bool graph[num_vertices][num_vertices],
                            int source) {
  if (source < 0 || source >= (int)num_vertices)
    return NULL;
  bool visited[num_vertices];
  for (size_t index = 0; index < num_vertices; ++index) {
    visited[index] = ((int)index == source);
  }

  SNode *path = SList_create(&source, sizeof(int));
  SNode *partial_paths = SList_create(&path, sizeof(SNode *));
  SNode *completed_paths = NULL;

  while (SList_length(partial_paths) > 0) {
    path = *(SNode **)partial_paths->data;
    int i = *(int *)path->data;
    SNode *continuations = NULL;
    for (int j = 0; j < (int)num_vertices; ++j) {
      if (!visited[j] && is_connected(num_vertices, graph, i, j)) {
        visited[j] = true;
        if (continuations == NULL) {
          continuations = SList_create(&j, sizeof(int));
        } else {
          SList_append(continuations, &j, sizeof(int));
        }
      }
    }
    if (SList_length(continuations) == 0) {
      if (completed_paths == NULL) {
        completed_paths = SList_create(&path, sizeof(SNode *));
      } else {
        SList_append(completed_paths, &path, sizeof(SNode *));
      }
      partial_paths = SList_pop_left(partial_paths);
    } else {
      size_t path_length = SList_length(path);
      for (size_t index = 0; index < SList_length(continuations); ++index) {
        SNode *new_path = SList_create(
            (int *)SList_get_data(continuations, index), sizeof(int));
        for (size_t path_index = 0; path_index < path_length; ++path_index) {
          SList_append(new_path, (int *)SList_get_data(path, path_index),
                       sizeof(int));
        }
        SList_append(partial_paths, &new_path, sizeof(SNode *));
      }
      SList_free(*(SNode **)partial_paths->data);
      partial_paths = SList_pop_left(partial_paths);
    }
    SList_free(continuations);
  }
  SList_free(partial_paths);
  return completed_paths;
}

int main() {
  /* a:
   * 0 ---> 1 <--> 5
   *  \     ^      ^
   *   \   /      /
   *    v v      v
   *     2 ---> 3 ---> 4
   */
  const size_t num_vertices = 6;
  const bool a[num_vertices][num_vertices] = {
      {0, 1, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 0},
      {0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0}, {0, 1, 0, 1, 0, 0},
  };
  printf("a:\n");
  for (int i = 0; i < (int)num_vertices; i++) {
    for (int j = 0; j < (int)num_vertices; j++) {
      printf("a[%d][%d] = %d\t", i, j, a[i][j]);
      printf("%d -> %d = %d\n", i, j, is_connected(num_vertices, a, i, j));
    }
  }

  const int source = 2;
  SNode *paths = breadth_first_search(num_vertices, a, source);

  printf("Breadth FirstSearch results starting from (%d):\n", source);
  while (paths != NULL) {
    SNode *node = *(SNode **)paths->data;
    printf("Complete path: ");
    while (node != NULL) {
      printf("%d", *(int *)node->data);
      if (node->next != NULL) {
        printf(" <- ");
      } else {
        printf("\n");
      }
      node = node->next;
    }
    SList_free(*(SNode **)paths->data);
    paths = SList_pop_left(paths);
  }

  return 0;
}
