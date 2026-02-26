#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  size_t capacity;
  size_t length;
  int *data;
} Vector;

/* Safe zero-init (makes vector_free always safe) */
static inline void vector_init(Vector *v) {
  if (!v)
    return;
  *v = (Vector){0};
}

/* Allocate an initial buffer (optional; you can also start with capacity=0) */
static inline bool vector_reserve(Vector *v, size_t capacity) {
  if (!v)
    return false;

  if (capacity == 0)
    capacity = 1;
  if (capacity > SIZE_MAX / sizeof *v->data)
    return false;

  int *p = (int *)malloc(capacity * sizeof *v->data);
  if (!p)
    return false;

  /* If v already had data, free it (simple behavior for now) */
  free(v->data);
  v->data = p;
  v->capacity = capacity;
  if (v->length > v->capacity)
    v->length = v->capacity;

  return true;
}

static inline void vector_free(Vector *v) {
  if (!v)
    return;
  free(v->data);
  *v = (Vector){0};
}

static inline bool vector_push(Vector *v, int value) {
  if (!v)
    return false;

  /* Grow if full */
  if (v->length == v->capacity) {
    size_t new_capacity = (v->capacity == 0) ? 1 : (v->capacity * 2);

    /* Overflow guard for bytes = new_capacity * sizeof(int) */
    if (new_capacity > SIZE_MAX / sizeof *v->data)
      return false;

    int *tmp = (int *)realloc(v->data, new_capacity * sizeof *v->data);
    if (!tmp)
      return false;

    v->data = tmp;
    v->capacity = new_capacity;
  }

  v->data[v->length++] = value;
  return true;
}

int main(void) {
  Vector v;
  vector_init(&v);

  /* optional: reserve upfront */
  if (!vector_reserve(&v, 3))
    return 1;

  if (!vector_push(&v, 10)) {
    vector_free(&v);
    return 1;
  }
  if (!vector_push(&v, 20)) {
    vector_free(&v);
    return 1;
  }
  if (!vector_push(&v, 30)) {
    vector_free(&v);
    return 1;
  }
  if (!vector_push(&v, 40)) {
    vector_free(&v);
    return 1;
  }

  for (size_t i = 0; i < v.length; i++) {
    printf("%d ", v.data[i]);
  }
  printf("\n");

  vector_free(&v);
  return 0;
}
