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
  bool value;
  UT_hash_handle hh;
} SeenNumberHashItem;

void add_num(SeenNumberHashItem **table, int key)
{
  SeenNumberHashItem *new_item;

  HASH_FIND_INT(*table, &key, new_item);

  if (!new_item)
  {
    new_item = malloc(sizeof(SeenNumberHashItem));
    new_item->key = key;
    new_item->value = true;
    HASH_ADD_INT(*table, key, new_item);
  }
}

int *answer;

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
void get_two_number_sum(int *array, size_t length, int targetSum)
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
      answer = malloc(2 * sizeof(int));
      answer[0] = current_number;
      answer[1] = target_number;
      return;
    }

    add_num(&table, array[i]);
  }
}

void two_number_sum()
{

  int numArray[] = {3, 5, -4, 8, 11, 1, -1, 6};
  size_t length = ARRAY_LEN(numArray);

  int targetSum = 10;
  get_two_number_sum(numArray, length, targetSum);

  printf("Answer:\n");

  if (answer)
  {
    printf("[%d, %d]\n", answer[0], answer[1]);
    free(answer);
  }
}