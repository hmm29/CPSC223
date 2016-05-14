/*
 * File: hash.h
 * Programmer: Harrison Miller
 * Description: this file contains function prototypes for the hash table for storing boggle words
 * and their counts.
 */

#ifndef HASH_H
#define HASH_H

struct entry {
	char *key;
	char *value;
  struct entry *next;
};

typedef struct entry entry_t;

struct hashtable {
	int size;
	struct entry **table;
};

typedef struct hashtable hashtable_t;

hashtable_t *ht_create(int size);
entry_t *ht_newpair(char *key, int value);
int ht_hash( hashtable_t *hashtable, char *key);
void ht_set(hashtable_t *hashtable, char *key, int value);
int ht_get(hashtable_t *hashtable, char *key);
void ht_sort(hashtable_t *hashtable);
void ht_print_values( hashtable_t *hashtable, int showNonBoggle);

#endif
/* end HASH_H */
