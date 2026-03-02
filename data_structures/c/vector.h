#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

/* Public API */

typedef struct Vector {
  size_t capacity;
  size_t length;
  int *data;
} Vector;

/* Lifecycle */
void vector_init(Vector *v);
void vector_free(Vector *v);

/* Capacity management */
bool vector_reserve(Vector *v, size_t capacity);

/* Modifiers */
bool vector_push(Vector *v, int value);
bool vector_pop(Vector *v, int *out);

/* Access */
bool vector_get(const Vector *v, size_t index, int *out);
bool vector_includes(const Vector *v, int target);

#endif /* VECTOR_H */
