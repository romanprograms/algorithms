#include <stdio.h>
#include "vector.h"
#include "stdlib.h"

void print_vector(Vector *v)
{
  printf("\nVector: ");
  for (size_t i = 0; i < v->size; i++)
  {
    printf("%d ", v->data[i]);
  }
  printf("\n");
}

int main(void)
{
  // heap allocation example. Stack version
  // would be Vector v = {0}
  Vector *v = malloc(sizeof(Vector));

  if (!v)
    return 1;

  vector_init(v);

  vector_push_back(v, 1);
  vector_push_back(v, 2);
  vector_push_back(v, 3);
  vector_push_back(v, 4);
  vector_push_back(v, 5);

  print_vector(v);

  int out_result;

  bool get_result = vector_get(v, 3, &out_result);

  printf("vector_get  at index %d\n", 3);

  if (get_result)
  {
    printf("vector_get result %d\n", out_result);
  }
  else
  {
    printf("vector_get result failed to get element at index %d", 3);
  }

  int pop_out;

  bool pop_result = vector_pop(v, &pop_out);

  if (pop_result)
  {
    printf("vector_pop result %d\n", pop_out);
  }
  else
  {
    printf("vector_pop result failed to pop element\n");
  }

  print_vector(v);

  vector_free(v);
  free(v);

  return 0;
}
