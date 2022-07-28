#include <stdbool.h>
#include <stdio.h>

#include "utils/list.h"

bool has_edge(size_t num_vertices, const bool graph[num_vertices][num_vertices],
              int source, int destination) {
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
      if (!visited[j] && has_edge(num_vertices, graph, i, j)) {
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

bool can_reach(size_t num_vertices, const bool a[num_vertices][num_vertices],
               int source, int destination) {
  bool can_reach = false;
  if (source < 0 || source >= (int)num_vertices || destination < 0 ||
      destination >= (int)num_vertices) {
    can_reach = false;
  } else if (source == destination) {
    can_reach = true;
  } else {
    SNode *paths = breadth_first_search(num_vertices, a, source);
    while (paths != NULL) {
      SNode *node = *(SNode **)paths->data;
      while (node != NULL) {
        if (node->data != NULL && *(int *)node->data == destination) {
          can_reach = true;
          break;
        }
        node = node->next;
      }
      SList_free(*(SNode **)paths->data);
      paths = SList_pop_left(paths);
    }
  }
  return can_reach;
}

SNode *strong_connected_components(size_t num_vertices,
                                   const bool a[num_vertices][num_vertices]) {
  bool visited[num_vertices];
  for (size_t index = 0; index < num_vertices; ++index) {
    visited[index] = false;
  }

  SNode *component = NULL;
  SNode *components = NULL;

  for (int i = 0; i < (int)num_vertices; ++i) {
    if (visited[i])
      continue;
    visited[i] = true;
    component = SList_create(&i, sizeof(int));
    if (components == NULL) {
      components = SList_create(&component, sizeof(SNode *));
    } else {
      SList_append(components, &component, sizeof(SNode *));
    }

    for (int j = 0; j < (int)num_vertices; ++j) {
      if (!visited[j] && can_reach(num_vertices, a, i, j) &&
          can_reach(num_vertices, a, j, i)) {
        visited[j] = true;
        SList_append(component, &j, sizeof(int));
      }
    }
  }

  return components;
}

int main() {
  /* a:
   * 0 ---> 1 <--> 5      6
   *  \     ^      ^      ^
   *   \   /      /      /
   *    v v      v      v
   *     2 ---> 3 ---> 4 ---> 7
   */
  const size_t num_vertices = 8;
  const bool a[num_vertices][num_vertices] = {
      // 0  1  2  3  4  5  6
      {0, 1, 1, 0, 0, 0, 0, 0}, // 0
      {0, 0, 1, 0, 0, 1, 0, 0}, // 1
      {0, 1, 0, 1, 0, 0, 0, 0}, // 2
      {0, 0, 0, 0, 1, 1, 0, 0}, // 3
      {0, 0, 0, 0, 0, 0, 1, 1}, // 4
      {0, 1, 0, 1, 0, 0, 0, 0}, // 5
      {0, 0, 0, 0, 1, 0, 0, 0}, // 6
      {0, 0, 0, 0, 1, 0, 0, 0}, // 7
  };
  printf("a:\n");
  for (int i = 0; i < (int)num_vertices; i++) {
    for (int j = 0; j < (int)num_vertices; j++) {
      printf("a[%d][%d] = %d\t", i, j, a[i][j]);
      printf("%d -> %d = %d\n", i, j, has_edge(num_vertices, a, i, j));
    }
  }

  const int source = 2;
  SNode *paths = breadth_first_search(num_vertices, a, source);

  printf("Breadth First Search results starting from (%d):\n", source);
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

  printf("Strongly connected components:\n");
  SNode *components = strong_connected_components(num_vertices, a);
  for (size_t index = 0; index < SList_length(components); ++index) {
    SNode *component = *(SNode **)SList_get_data(components, index);
    size_t node_length = SList_length(component);
    printf("{");
    for (size_t node = 0; node < node_length; ++node) {
      printf("%d", *(int *)SList_get_data(component, node));
      if (node + 1 < node_length) {
        printf(", ");
      }
    }
    printf("}\n");
    SList_free(component);
  }

  SList_free(components);

  return 0;
}
