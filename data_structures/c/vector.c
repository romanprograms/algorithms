#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  size_t capacity;
  size_t length;
  int *array;

} Vector;

bool vector_new(Vector *v, size_t capacity) {
  v->capacity = capacity;
  v->length = 0;
  v->array = malloc(capacity * sizeof(int));

  if (!v->array) {
    return false;
  }
  return true;
}

bool vector_add(Vector *v, int element) {
  if (v->length == v->capacity) {
    printf("Capacity reached. Making new allocation!\n");

    size_t new_capacity = v->capacity * 2;
    // maybe use realloc ?
    int *new_array = malloc(new_capacity * sizeof(int));
    if (!new_array) {
      return false;
    }
    v->capacity = new_capacity;
    // copy existing array into new int* array
    for (int i = 0; i < v->length; i++) {
      new_array[i] = v->array[i];
    }
    // free the old array
    free(v->array);
    v->array = new_array;
  }

  if (v->length < v->capacity) {
    v->array[v->length] = element;
    v->length++;
  }

  return true;
}

void vector_print(Vector *v) {
  for (size_t i = 0; i < v->length; i++) {
    printf("%d, ", v->array[i]);
  }
}

int main(void) {
  Vector v;
  bool res = vector_new(&v, 3);

  if (!res)
    return 1;

  vector_add(&v, 1);
  vector_add(&v, 2);
  vector_add(&v, 3);
  vector_add(&v, 4);
  vector_add(&v, 5);

  printf("Printing v ");

  vector_print(&v);

  printf("\n");
  return 0;
}
