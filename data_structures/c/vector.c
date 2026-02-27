#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TRYV(vecptr, expr)                                                     \
  do {                                                                         \
    if (!(expr)) {                                                             \
      vector_free((vecptr));                                                   \
      return 1;                                                                \
    }                                                                          \
  } while (0)

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

static inline bool vector_get(const Vector *v, size_t index, int *out) {
  if (!v || !out)
    return false;
  if (index >= v->length)
    return false;

  *out = v->data[index];
  return true;
}

static inline bool vector_pop(Vector *v, int *out) {
  if (!v || !out)
    return false;
  if (v->length == 0)
    return false;

  *out = v->data[v->length - 1];
  v->length--;

  if (v->capacity > 1 && v->length <= v->capacity / 4) {
    size_t new_capacity = v->capacity / 2;
    if (new_capacity == 0)
      new_capacity = 1;
    if (new_capacity < v->length)
      new_capacity = v->length;

    if (new_capacity <= SIZE_MAX / sizeof *v->data) {
      int *tmp = realloc(v->data, new_capacity * sizeof *v->data);
      if (tmp) {
        v->data = tmp;
        v->capacity = new_capacity;
      }
    }
  }

  return true;
}

// static inline int vector_pop(Vector *v, size_t index) {}

int main(void) {
  Vector v;
  vector_init(&v);

  TRYV(&v, vector_reserve(&v, 3));

  TRYV(&v, vector_push(&v, 1));
  TRYV(&v, vector_push(&v, 2));
  TRYV(&v, vector_push(&v, 3));
  TRYV(&v, vector_push(&v, 4));
  TRYV(&v, vector_push(&v, 5));

  for (size_t i = 0; i < v.length; i++) {
    printf("%d ", v.data[i]);
  }
  printf("\n");

  int pop_res;
  vector_pop(&v, &pop_res);
  printf("Pop result %d\n", pop_res);

  int x;
  if (!vector_get(&v, 3, &x)) {
    vector_free(&v);
    return 1;
  }
  printf("%d\n", x); // prints 40

  vector_free(&v);
  return 0;
}
