#include "vector.h"
//  printf
#include <stdio.h>
//  bool
#include <stdbool.h>
//  realloc
#include <stdlib.h>
//  SIZE_MAX
#include <stdint.h>
#include <assert.h>

void vector_init(Vector *v)
{
  assert(v != NULL);
  v->size = 0;
  v->capacity = 0;
  v->data = NULL;
}

static bool vector_grow(Vector *v)
{
  if (v->size < v->capacity)
  {
    // there's still unfilled slots
    return true;
  }

  size_t new_capacity;

  if (v->capacity == 0)
    new_capacity = 4;
  else
  {
    if (SIZE_MAX - v->capacity < v->capacity)
      return false;
    new_capacity = v->capacity * 2;
  }

  if (new_capacity > SIZE_MAX / sizeof(typeof(*(v->data))))
    return false;

  int *new_data = realloc(v->data, new_capacity * sizeof(typeof(*(v->data))));

  if (new_data == NULL)
    return false;

  v->data = new_data;

  v->capacity = new_capacity;

  return true;
}

void vector_free(Vector *v)
{
  assert(v != NULL);

  free(v->data);

  v->capacity = 0;
  v->size = 0;
  v->data = NULL;
}

static bool vector_shrink(Vector *v)
{
  if (v->size > v->capacity / 4)
    return true;

  if (v->size == 0)
  {
    vector_free(v);
    return true;
  }

  size_t new_capacity = v->capacity / 2;

  int *new_data = realloc(v->data, sizeof(typeof(*(v->data))) * new_capacity);

  if (!new_data)
    return false;

  v->data = new_data;
  v->capacity = new_capacity;
  return true;
}

bool vector_push_back(Vector *v, int new_element)
{
  assert(v != NULL);

  bool result = vector_grow(v);
  if (!result)
    return false;

  v->data[v->size] = new_element;
  v->size = v->size + 1;
  return true;
}

bool vector_reserve(Vector *v, size_t capacity)
{
  assert(v != NULL);

  if (capacity == v->capacity)
    return true;

  if (capacity < v->capacity)
    return false;

  if (capacity > SIZE_MAX / sizeof(typeof(*(v->data))))
    return false;

  int *new_data = realloc(v->data, sizeof(typeof(*(v->data))) * capacity);

  // check if realloc fails
  if (!new_data)
    return false;

  v->data = new_data;
  v->capacity = capacity;
  return true;
}

// if we shrink at 1/2 capacity and the user pushes/pops around that boundary,
// we'd be constantly allocating and deallocating (thrashing).
// 1/4 gives us a buffer zone.
bool vector_pop(Vector *v, int *out)
{
  assert(v != NULL);

  if (v->size == 0)
    return false;

  if (out != NULL)
  {
    *out = v->data[v->size - 1];
  }

  v->size--;

  vector_shrink(v);

  return true;
}

bool vector_get(Vector *v, size_t index, int *out)
{
  assert(v != NULL);

  if (index >= v->size)
    return false;

  *out = v->data[index];

  return true;
}