#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

/* Public API */

typedef struct Vector
{
  size_t size;
  size_t capacity;
  int *data;
} Vector;

/* Lifecycle */
void vector_init(Vector *v);
void vector_free(Vector *v);

/* Capacity management */
bool vector_reserve(Vector *v, size_t capacity);

/* Modifiers */
bool vector_push_back(Vector *v, int new_element);
bool vector_pop(Vector *v, int *out);

/* Access */
bool vector_get(Vector *v, size_t index, int *out);

#endif /* VECTOR_H */
