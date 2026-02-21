#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
  char *key;
  char *value;
} Entry;

typedef struct LookupTable {
  size_t count;
  size_t capacity;
  Entry *entries;
} LookupTable;

LookupTable table;

void lt_init(LookupTable *table) {
  table->count = 0;
  table->capacity = 4;
  table->entries = malloc(table->capacity * sizeof(Entry));
}

void lt_add(LookupTable *table, const char *key, const char *value) {
  if (table->count >= table->capacity) {
    table->capacity *= 2;
    table->entries = realloc(table->entries, table->capacity * sizeof(Entry));
  }

  table->entries[table->count].key = strdup(key);
  table->entries[table->count].value = strdup(value);
  table->count++;
}

const char *lt_get(LookupTable *table, const char *key) {
  for (size_t i = 0; i < table->count; i++) {
    if (strcmp(table->entries[i].key, key) == 0) {
      return table->entries[i].value;
    }
  }
  return NULL;
}

void lt_free(LookupTable *table) {
  for (size_t i = 0; i < table->count; i++) {
    free(table->entries[i].key);
    free(table->entries[i].value);
  }
  free(table->entries);
}

int main() {
  LookupTable table;
  lt_init(&table);

  lt_add(&table, "name", "Roman");
  lt_add(&table, "language", "C");
  lt_add(&table, "engine", "raylib");

  printf("name: %s\n", lt_get(&table, "name"));
  printf("engine: %s\n", lt_get(&table, "engine"));

  lt_free(&table);
}
