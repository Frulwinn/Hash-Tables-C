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
  int capacity; //number of buckets/array size
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
  //allocate memory for the basic hash table struct
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));
  //set initial values for capacity
  ht->capacity = capacity;
  //allocate memory for the storage to hold the capacity number pairs(key,value)
  ht->storage = calloc(capacity, sizeof(Pair *));

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  //hash the key to get an index
  unsigned int hash_index = hash(key, ht->capacity); // capacity

  //create a pair with the key/value
  Pair *pair = create_pair(key, value);

  // Create a variable to hold the hash index
  Pair *currently_stored_pair = ht->storage[hash_index];
  //if the stored pair already, if the bucket is already full
  if (stored_pair != NULL) {
    //compare the keys if they don't match
    if (strcmp (key, stored_pair->key) != 0) {
        //print warning
        printf("Warning: we don't have a collision system; going to overwrite previous value in hash table! \n")
      }
      //otherwise delete the pair that was previously in that index
      destroy_pair(stored_pair);

    }
    //insert the pair in the hashed index
    ht->storage[index] = pair;

}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  //hash our key to get an index
  int index = hash(key, ht->capacity); //capacity == how many "buckets" we have

  //check if there's a valid entry in our bucket
  //second part means if you are going through a linkedlist and get the same index
  //different key but same index problem
  if (ht->storage[index] == NULL || strcmp(ht->storage[index]->key, key) !=0) {
    fprintf(stderr, "Unable to remove entry with this key: %s \n", key);


  } else {

    destroy_pair(ht->storage[index]);
    ht->storage[index] = NULL;
  }
}


/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  //hash our key to get an index
  int index = has(key, ht->capacity); //capacity == how many "buckets" we have
  //checking if index is null and the key is matching
  if (ht->storage[index] != NULL && strcmp(key, ht->storage[index]->key, key) == 0) {

    return ht->storage[index]->value;
  }
  fprint(stderr, "unable to find entry with your key: %s \n", key);
  return NULL;
  
}


/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
    //loop through each pair in the hash table's capacity
    for (int i = 0; i < ht->capacity; i++) {
      //if there is a pair, destroy it
      if (ht->storage[i] != NULL) {
        destroy_pair(ht->storage[i]);
      }
    }
    //free all storage
    free(ht->storage);
    //free the hash table
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
