#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_init_and_free() {
  printf("Testing init and free...\n");
  Vector v;
  vector_init(&v);
  assert(v.capacity == 0);
  assert(v.length == 0);
  assert(v.data == NULL);
  vector_free(&v);
  assert(v.capacity == 0);
  assert(v.length == 0);
  assert(v.data == NULL);
  printf("✓ Init and free\n");
}

void test_push_and_get() {
  printf("Testing push and get...\n");
  Vector v;
  vector_init(&v);
  
  // Push some values
  assert(vector_push(&v, 10) == true);
  assert(vector_push(&v, 20) == true);
  assert(vector_push(&v, 30) == true);
  assert(v.length == 3);
  
  // Get values
  int val;
  assert(vector_get(&v, 0, &val) == true);
  assert(val == 10);
  assert(vector_get(&v, 1, &val) == true);
  assert(val == 20);
  assert(vector_get(&v, 2, &val) == true);
  assert(val == 30);
  
  // Out of bounds
  assert(vector_get(&v, 3, &val) == false);
  
  vector_free(&v);
  printf("✓ Push and get\n");
}

void test_pop() {
  printf("Testing pop...\n");
  Vector v;
  vector_init(&v);
  
  // Pop from empty vector
  int val;
  assert(vector_pop(&v, &val) == false);
  
  // Push and pop
  vector_push(&v, 10);
  vector_push(&v, 20);
  vector_push(&v, 30);
  
  assert(vector_pop(&v, &val) == true);
  assert(val == 30);
  assert(v.length == 2);
  
  assert(vector_pop(&v, &val) == true);
  assert(val == 20);
  assert(v.length == 1);
  
  assert(vector_pop(&v, &val) == true);
  assert(val == 10);
  assert(v.length == 0);
  
  assert(vector_pop(&v, &val) == false);
  
  vector_free(&v);
  printf("✓ Pop\n");
}

void test_reserve() {
  printf("Testing reserve...\n");
  Vector v;
  vector_init(&v);
  
  // Reserve on empty vector
  assert(vector_reserve(&v, 10) == true);
  assert(v.capacity >= 10);
  assert(v.length == 0);
  
  // Push some data
  vector_push(&v, 1);
  vector_push(&v, 2);
  vector_push(&v, 3);
  
  // Reserve more (should preserve data)
  assert(vector_reserve(&v, 20) == true);
  assert(v.capacity >= 20);
  assert(v.length == 3);
  
  // Verify data is preserved
  int val;
  assert(vector_get(&v, 0, &val) == true && val == 1);
  assert(vector_get(&v, 1, &val) == true && val == 2);
  assert(vector_get(&v, 2, &val) == true && val == 3);
  
  // Reserve less than current capacity (should do nothing)
  size_t old_capacity = v.capacity;
  assert(vector_reserve(&v, 5) == true);
  assert(v.capacity == old_capacity);
  
  vector_free(&v);
  printf("✓ Reserve\n");
}

void test_includes() {
  printf("Testing includes...\n");
  Vector v;
  vector_init(&v);
  
  assert(vector_includes(&v, 10) == false);
  
  vector_push(&v, 10);
  vector_push(&v, 20);
  vector_push(&v, 30);
  
  assert(vector_includes(&v, 10) == true);
  assert(vector_includes(&v, 20) == true);
  assert(vector_includes(&v, 30) == true);
  assert(vector_includes(&v, 40) == false);
  
  vector_free(&v);
  printf("✓ Includes\n");
}

void test_capacity_growth() {
  printf("Testing capacity growth...\n");
  Vector v;
  vector_init(&v);
  
  // Track capacity changes
  size_t last_capacity = 0;
  for (int i = 0; i < 100; i++) {
    vector_push(&v, i);
    if (v.capacity > last_capacity) {
      printf("  Capacity grew from %zu to %zu at length %zu\n", 
             last_capacity, v.capacity, v.length);
      last_capacity = v.capacity;
    }
  }
  
  assert(v.length == 100);
  
  // Verify all values
  int val;
  for (int i = 0; i < 100; i++) {
    assert(vector_get(&v, i, &val) == true);
    assert(val == i);
  }
  
  vector_free(&v);
  printf("✓ Capacity growth\n");
}

void test_capacity_shrink() {
  printf("Testing capacity shrink on pop...\n");
  Vector v;
  vector_init(&v);
  
  // Fill vector
  for (int i = 0; i < 16; i++) {
    vector_push(&v, i);
  }
  size_t initial_capacity = v.capacity;
  printf("  Initial capacity: %zu, length: %zu\n", v.capacity, v.length);
  
  // Pop until we trigger shrink (at 1/4 capacity)
  int val;
  while (v.length > initial_capacity / 4) {
    vector_pop(&v, &val);
  }
  
  // One more pop should trigger shrink
  size_t old_capacity = v.capacity;
  vector_pop(&v, &val);
  printf("  After shrink - capacity: %zu, length: %zu\n", v.capacity, v.length);
  assert(v.capacity < old_capacity);
  
  vector_free(&v);
  printf("✓ Capacity shrink\n");
}

void test_null_checks() {
  printf("Testing null parameter handling...\n");
  
  // Test with NULL vector pointer
  assert(vector_push(NULL, 10) == false);
  assert(vector_reserve(NULL, 10) == false);
  assert(vector_includes(NULL, 10) == false);
  
  int val;
  assert(vector_get(NULL, 0, &val) == false);
  assert(vector_pop(NULL, &val) == false);
  
  // Test with NULL output parameter
  Vector v;
  vector_init(&v);
  vector_push(&v, 10);
  
  assert(vector_get(&v, 0, NULL) == false);
  assert(vector_pop(&v, NULL) == false);
  
  vector_free(&v);
  printf("✓ Null checks\n");
}

int main(void) {
  printf("Running vector tests...\n\n");
  
  test_init_and_free();
  test_push_and_get();
  test_pop();
  test_reserve();
  test_includes();
  test_capacity_growth();
  test_capacity_shrink();
  test_null_checks();
  
  printf("\nAll tests passed! ✓\n");
  return 0;
}