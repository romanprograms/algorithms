#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "uthash.h"

#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

void printArray(int *array, size_t length)
{
  printf("\nArray: [");
  for (size_t i = 0; i < length; i++)
  {
    printf("%d ", array[i]);
  }
  printf("] ");
}

typedef struct SeenNumberHashItem
{
  int key;
  UT_hash_handle hh;
} SeenNumberHashItem;

bool add_num(SeenNumberHashItem **table, int key)
{
  SeenNumberHashItem *new_item;

  HASH_FIND_INT(*table, &key, new_item);

  if (!new_item)
  {
    new_item = malloc(sizeof(SeenNumberHashItem));
    if (!new_item)
    {
      return false;
    }
    new_item->key = key;
    HASH_ADD_INT(*table, key, new_item);
    return true;
  }
  return false;
}

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
int *get_two_number_sum(int *array, size_t length, int targetSum)
{
  struct SeenNumberHashItem *table = NULL;

  struct SeenNumberHashItem *new_item;

  for (size_t i = 0; i < length; i++)
  {
    int target_number = targetSum - array[i];
    HASH_FIND_INT(table, &target_number, new_item);
    if (new_item)
    {
      int current_number = array[i];
      int *answer = malloc(2 * sizeof(int));
      if (!answer)
      {
        return NULL;
      }
      answer[0] = current_number;
      answer[1] = target_number;
      return answer;
    }

    add_num(&table, array[i]);
  }

  return NULL;
}

void two_number_sum()
{

  int numArray[] = {3, 5, -4, 8, 11, 1, -1, 6};
  size_t length = ARRAY_LEN(numArray);

  int targetSum = 10;
  int *answer = get_two_number_sum(numArray, length, targetSum);

  printf("Answer:\n");

  if (answer)
  {
    printf("[%d, %d]\n", answer[0], answer[1]);
    free(answer);
  }
}