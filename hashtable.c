#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"
#include "hashtable.h"


/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots){
	//printf("hello from hashtable_new!");
	//if the num_slots is not valid, return null
	if(num_slots <= 0){
		return NULL;
	}
	/*set_t table[num_slots];
	hashtable_t *out;
	out->head = table[0]; */
	
	int i;
	hashtable_t *out = (hashtable_t*)malloc(sizeof(hashtable_t));
	//hashtable_t *out;
	if(out == NULL){
		return NULL;
	}
	//creates bins
	out->nodes = (set_t**)malloc(sizeof(set_t*)*num_slots);
	out->size = num_slots;
	for(i = 0; i < num_slots;i++){
		//memory is being allocated here
		out->nodes[i] = set_new();
	}
	
	return out;
	
}

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
	//printf("hello from ht_insert!");
	
	int i;
	
	//char* newkey = (char*)malloc(sizeof(key));
	//newkey = strcpy(newkey,key);
	
	//look through this bin for the key, if not found, then return false, else set_insert
	if(ht == NULL || key == NULL || item == NULL){
		return false;
	}
	//printf("finished null check\n");
	//iterates through entire hash table to check if key exists
	for(i=0; i < ht->size;i++){
		//for( ; setnode != NULL; setnode = setnode->next){ 
		if(set_find(ht->nodes[i],key) != NULL){
			return false;
		}
			/*if(strcmp(setnode->key,key)==0){
				return false;
			} */
	} 
	//printf("finished for loop\n");
	char* newkey = strdup(key);
	int index = atoi(newkey)%(ht->size);
	set_insert(ht->nodes[index],newkey,item);
	//printf("finished insert\n");
	free(newkey);
	//printf("freed key");
	return true;
}

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key){
	int i;
	//checks if any of the parameters are null
	if(ht == NULL || key == NULL){
		return NULL;
	}
	//printf("passed null check");
	//checks if key is found
	/*for(i=0; i < ht->size;i++){
		printf("%s", key);
		//if statement checks each bin's set for the given key
		if(set_find(ht->nodes[i],key) == NULL){
			return NULL;
		}
	} */
	
	//for loop iterates through ht array
	//returns NULL if key is not found due to nature of set_find
	//or returns item if key is found
	for(i=0; i < ht->size;i++){
		return set_find(ht->nodes[i],key);
	}
	return set_find(ht->nodes[i],key);
}

/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht){
	int i;
	if(ht != NULL){
		//for loop iterates through hashtable/bins
		for(i=0; i < ht->size; i++){
			if(ht->nodes[i] != NULL){
			//will delete the set in the given bin
				set_delete(ht->nodes[i]);
				//printf("deleted set!");
			}
		}
		//frees the bins
		free(ht->nodes);
		//printf("freed bins");
		//frees the hashtable
		free(ht);
		//printf("freed ht");
	}
} 
