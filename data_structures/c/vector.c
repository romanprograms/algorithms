#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  size_t capacity;
  size_t length;
  int *array;

} Vector;

bool vector_new(Vector *v, size_t capacity) {
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
  if (v->length == v->capacity) {
    printf("Trying to insert %d. Capacity reached. Making new allocation!\n",
           element);

    if (v->capacity > SIZE_MAX / 2)
      return false;

    size_t new_capacity = v->capacity * 2;
    // guard against overflowing size_t and allocating too small a buffer
    // buffer overflow later.
    if (new_capacity > SIZE_MAX / sizeof *v->array)
      return false;

    // maybe use realloc ?
    int *new_array = malloc(new_capacity * sizeof(*v->array));

    if (!new_array) {
      return false;
    }

    // copy existing array into new int* array
    for (size_t i = 0; i < v->length; i++) {
      new_array[i] = v->array[i];
    }
    // free the old array
    free(v->array);
    v->array = new_array;
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

  if (!vector_add(&v, 1)) {
    vector_free(&v);
    return 1;
  }
  if (!vector_add(&v, 2)) {
    vector_free(&v);
    return 1;
  }
  if (!vector_add(&v, 3)) {
    vector_free(&v);
    return 1;
  }
  if (!vector_add(&v, 4)) {
    vector_free(&v);
    return 1;
  }
  if (!vector_add(&v, 5)) {
    vector_free(&v);
    return 1;
  }

  printf("Printing v ");

  vector_print(&v);

  printf("\n");

  vector_free(&v);
  return 0;
}
