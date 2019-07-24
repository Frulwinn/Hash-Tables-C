#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity;
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  BasicHashTable *ht;
  //for case where capacity is 0 or less return NULL
  if (capacity < 1) {
    return NULL;
  }
  //mallocing space for hashtable
  ht = malloc(sizeof(BasicHashTable));
  if (ht == NULL) {
    return NULL;
  }

  //mallocing space for size of storage
  ht->storage = (Pair**)malloc(capacity * sizeof(Pair));
  if (ht->storage == NULL) {
    return NULL;
  }
  //fill block of memory with capacity
  //use calloc instead
  memset(ht->storage, 0, capacity * sizeof(Pair));
  ht->capacity = capacity;

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  //node pointer points to Pair that has the key and value
  Pair *node;

  if (ht == NULL) {
    return 1;
  }

  node = malloc(sizeof(Pair));
  if(node == NULL) {
    return 1;
  }
  //copy of key and value is created
  node->key = strdup(key);
  node->value = strdup(value);

  //need to insert key and value
  //not finished need to complete
  node_handler(ht, node);


  return 0;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{

}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  char *key_cp;
  int i;
  Pair *p;

  if (ht == NULL) {
    return NULL;
  }
  //creates copy for key
  key_cp = strdup(key);
  //hash key and hash table capacity
  i = hash(key, ht->capacity);
  //puts pair into hash table storage
  p = ht->storage[i];

  //while pair is not empty  compary pair key and key copy 
  while (p != NULL) {
    if(strcmp(p->key, key_cp) == 0) {
      break;
    }
    //go to next pair
    p = p->next;
  }
  //free the copy
  free(key_cp);

  if(p == NULL) {
    return NULL;
  }

  return p->value;

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  Pair *p;
  int i;

  if (ht == NULL) {
    return;
  }

  for (i = 0; i < ht->capacity; ++i {
    //while hash tabel storage is not NULL traverse
    if (ht->storage[i] != NULL) {
      //traverse the list and free the nodes
      while(ht->array[i] != NULL) {
        p = ht->storage[i]->next;
        free(ht->storage[i]->key);
        free(ht->storage[i]->value);
        free(ht->storage[i]);
        //after freeing the key, value, and storage you still have the pair pointer
        ht->storage[i] = p
      }
      free(ht->storage[i]);
    }
  }
  free(ht->storage);
  free(ht);
}


#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
