#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"


/* Create a new (empty) set; return NULL if error. */
set_t* set_new(void){
	//printf("hello from set_new!");
	set_t *out = (set_t*)malloc(sizeof(set_t));
	if(out == NULL){
		return NULL;
	}
	out->head = NULL;
	return out;
}

/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool set_insert(set_t *set, const char *key, void *item){
	//printf("hello from set_insert!");
	//char *newkey = (char*)malloc(sizeof(key));
	//checks if any parameter is null
	if(set == NULL || key == NULL || item == NULL){
		return false;
	}
	
	setnode_t *current = set->head;
	//checks if the key exists within the set
	while(current != NULL){
		if(strcmp(current->key,key) == 0){
			return false;
		}
		current = current->next;
	}
	 /*for(p=set->head; p->next != NULL; p = p->next){
		if(p->key == key){
			return false;
		}
	} */
	//creates a new node in the set
	setnode_t *newnode = (setnode_t*)malloc(sizeof(setnode_t));
	//newnode->key = strcpy(newkey,key);
	newnode->key = strdup(key);
	newnode->item = item;
	newnode->next = set->head;
	newnode->prev = NULL;
	
	if((set->head != NULL)){
		set->head->prev = newnode;
	}
	
	set->head = newnode;
	return true;
	
}

void *find_helper(setnode_t *node, const char *key){
	//if the key is not found or if the set is null, return null
	if(node == NULL){
		return NULL;
	} //if the key is found, return the item
	else if(strcmp(node->key,key)== 0){
		return node->item;
	} //else statements iterates through set recursively
	else{
		return find_helper(node->next,key);
	}
}

/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *set_find(set_t *set, const char *key){
	//returns null if the set is null or the key is null
	if(set == NULL || key == NULL){
		//printf("hello world!!!");
		return NULL;
	}
	return find_helper(set->head,key);
}


/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
void set_print(set_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) ){
	//checks if set is null
	if(fp != NULL){
		if(set == NULL){
			fprintf(fp,"(null)");
		}
		setnode_t *current = set->head;
		while(current != NULL){
			if(itemprint != NULL){
				itemprint(fp, current->key, current->item);
			}
			current = current->next;
		} 
	}

}

/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) ){
        setnode_t *current = set->head;
        if(set != NULL || itemfunc != NULL){
                 	while(current != NULL){
                 		itemfunc(arg, current->key,current->item);
                 		current = current->next;
                 	}
                 }
}

/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
void set_delete(set_t *set){
	setnode_t *p;
	setnode_t *temp = set->head;
	
	for( ; temp != NULL; temp = p){ 
		//p will store the next key-item pair in the set
		p = temp->next;
		free(temp->key);
		//free(temp->item);
		free(temp);
	} 
	free(set);
}
