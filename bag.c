#include "bag.h"
#include "crawler.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

bag_t* bag_new(void){
	//printf("hello from bag_new!");
	bag_t *out = (bag_t*)malloc(sizeof(bag_t));
	if(out == NULL){
		return NULL;
	}
	out->head = NULL;
	out->size = 0;
	return out;
}

bool bag_insert(bag_t *bag, webpage_t *page){
	//printf("hello from the bag_insert!");
	if(bag == NULL || page == NULL){
		return false;
	}
	bagnode_t *current = bag->head;
	//checks if key already exists in bag
	while(current != NULL){
		if(current->page == page){
			return false;
		}
		current = current->next;
	}
	//creates a new node in bag
	bagnode_t *newnode = (bagnode_t*)malloc(sizeof(bagnode_t));
	newnode->page = page;
	newnode->next = bag->head;

	bag->head = newnode;
	bag->size++;
	return true;
}
//function to take out a webpage from head and delete it
webpage_t *bag_pull(bag_t *bag){
	//printf("hello from the bag_pull!");
	bagnode_t *p;
	//temp is the current head of bag
	bagnode_t *temp = bag->head;
	webpage_t *out;
	
	//p is the next head
	p=temp->next;
	//out is the webpage from the previous head
	out = temp->page;
	free(temp);
	
	if(p != NULL){
		//if the previous head wasn't the last item, the new head is the next value
		bag->head = p;
	} else{
		//else, the last value will be NULL
		bag->head = NULL;
	}
	
	//free(bag);
	bag->size--;
	
	return out;
}
