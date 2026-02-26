#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TRYV(vecptr, expr)                                                     \
  do {                                                                         \
    if (!(expr)) {                                                             \
      vector_free(vecptr);                                                     \
      return 1;                                                                \
    }                                                                          \
  } while (0)

typedef struct Vector {
  size_t capacity;
  size_t length;
  int *array;

} Vector;

bool vector_new(Vector *v, size_t capacity) {
  if (!v)
    return false;

  if (capacity == 0) {
    v->capacity = 1;
  } else {
    v->capacity = capacity;
  }
  v->length = 0;
  v->array = malloc(v->capacity * sizeof(*v->array));

  if (!v->array) {
    return false;
  }
  return true;
}

bool vector_add(Vector *v, int element) {
  if (!v)
    return false;

  if (v->length == v->capacity) {
    printf("Trying to insert %d. Capacity reached. Making new allocation!\n",
           element);

    size_t new_capacity = v->capacity ? v->capacity * 2 : 1;
    if (new_capacity > SIZE_MAX / sizeof *v->array)
      return false;

    int *tmp = realloc(v->array, new_capacity * sizeof *v->array);
    if (!tmp)
      return false;

    v->array = tmp;
    v->capacity = new_capacity;
  }

  v->array[v->length] = element;
  v->length++;

  return true;
}

void vector_free(Vector *v) {
  free(v->array);
  v->array = NULL;
  v->capacity = 0;
  v->length = 0;
}

void vector_print(const Vector *v) {
  printf("[");
  for (size_t i = 0; i < v->length; i++) {
    if (i == v->length - 1) {
      printf("%d", v->array[i]);
    } else {
      printf("%d, ", v->array[i]);
    }
  }
  printf("]");
}

int main(void) {
  Vector v;
  bool res = vector_new(&v, 3);

  if (!res)
    return 1;

  TRYV(&v, vector_add(&v, 1));
  TRYV(&v, vector_add(&v, 2));
  TRYV(&v, vector_add(&v, 3));
  TRYV(&v, vector_add(&v, 4));
  TRYV(&v, vector_add(&v, 5));

  printf("Printing v ");

  vector_print(&v);

  printf("\n");

  vector_free(&v);
  return 0;
}
