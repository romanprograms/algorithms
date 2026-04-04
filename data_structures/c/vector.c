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

typedef struct Vector
{
  size_t size;
  size_t capacity;
  int *data;
} Vector;

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

  if (new_capacity > SIZE_MAX / sizeof(int))
    return false;

  int *new_data = realloc(v->data, new_capacity * sizeof(int));

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
  // shrink to fit
  // checking for size being bigger than capacity is odd
  // since it shouldn't happen, but it's probably safer that way.
  if (v->size > v->capacity)
    return false;

  if (v->size == v->capacity)
    return true;

  size_t new_capacity;

  if (v->size > 0)
  {
    new_capacity = v->size;
  }
  else
  {
    vector_free(v);
    return true;
  }

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

  if (capacity > SIZE_MAX / sizeof(int))
    return false;

  int *new_data = realloc(v->data, sizeof(int) * capacity);

  // check if realloc fails
  if (!new_data)
    return false;

  v->data = new_data;
  v->capacity = capacity;
  return true;
}