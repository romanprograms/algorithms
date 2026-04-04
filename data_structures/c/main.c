#include <stdio.h>
#include "vector.h"

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

  printf("Vector ==============\n");
  for (size_t i = 0; i < v->size; i++)
  {
    printf("%d ", v->data[i]);
  }
  printf("\n==============\n");

  vector_free(v);
  free(v);

  return 0;
}
