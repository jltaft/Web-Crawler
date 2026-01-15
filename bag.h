#ifndef BAG_H
#define BAG_H

#include "crawler.h"
#include <stdbool.h>

typedef struct bagnode {
	struct bagnode *next;
	webpage_t *page;
} bagnode_t;

typedef struct bag {
	bagnode_t *head;
	int size;
} bag_t;

bag_t* bag_new(void);

bool bag_insert(bag_t *bag, webpage_t *page);

webpage_t *bag_pull(bag_t *bag);

#endif // BAG_H
