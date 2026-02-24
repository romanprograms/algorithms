/*
 * Two Number Sum
 *
 * Write a function that takes in a non-empty array of distinct integers and an
 * integer representing a target sum. If any two numbers in the input array sum
 * up to the target sum, the function should return them in an array, in any
 * order. If no two numbers sum up to the target sum, the function should return
 * an empty array.
 *
 */

#include "uthash.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

typedef struct SeenNumber {
  int key;           // the number we’ve seen
  UT_hash_handle hh; // makes this struct hashable
} SeenNumber;

/* Insert key into the hash table if it isn't already there.
   Returns true on success, false on allocation failure. */
static bool seen_insert(SeenNumber **table, int key) {
  SeenNumber *item = NULL;
  HASH_FIND_INT(*table, &key, item);
  if (item)
    return true; // already present => still “success”

  item = (SeenNumber *)malloc(sizeof(*item));
  if (!item)
    return false;

  item->key = key;
  HASH_ADD_INT(*table, key, item);
  return true;
}

/* Free all items in the hash table and set head to NULL. */
static void seen_free_all(SeenNumber **table) {
  SeenNumber *cur = NULL, *tmp = NULL;
  HASH_ITER(hh, *table, cur, tmp) {
    HASH_DEL(*table, cur);
    free(cur);
  }
  *table = NULL;
}

/* Returns true and writes the pair into out[2] if found.
   Returns false if not found OR if allocation failed (in which case no result).
 */
bool two_number_sum(const int *array, size_t length, int targetSum,
                    int out[2]) {
  SeenNumber *table = NULL;
  bool found = false;

  for (size_t i = 0; i < length; i++) {
    int current = array[i];
    int complement = targetSum - current;

    SeenNumber *hit = NULL;
    HASH_FIND_INT(table, &complement, hit);
    if (hit) {
      out[0] = current;
      out[1] = complement;
      found = true;
      goto cleanup;
    }

    if (!seen_insert(&table, current)) {
      // allocation failure
      found = false;
      goto cleanup;
    }
  }

cleanup:
  seen_free_all(&table);
  return found;
}

/* Demo */
int main(void) {
  int numArray[] = {3, 5, -4, 8, 11, 1, -1, 6};
  size_t length = ARRAY_LEN(numArray);
  int targetSum = 10;

  int ans[2];
  if (two_number_sum(numArray, length, targetSum, ans)) {
    printf("[%d, %d]\n", ans[0], ans[1]);
  } else {
    printf("No pair found (or allocation failed).\n");
  }

  return 0;
}
