#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

#include "crawler.h"
#include "curl.h"
#include "url.h"
#include "pagedir.h"
#include "bag.h"
#include "hashtable.h"

static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);
/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
	// Fill in with your implementation
	//printf("hello from parseArgs!");
	
	if(seedURL == NULL){
		fprintf(stderr,"Invalid seedURL\n");
		exit(1);
	}
	//if the number of arguments is not equal to 3
	if(argc != 4){
		fprintf(stderr, "Invalid number of arguments\n");
		exit(1);
	}
	if(pagedir_init(*pageDirectory)==false){
		fprintf(stderr, "Invalid pageDirectory\n");
		exit(1);
	}
	if(*maxDepth >= 11 || *maxDepth <= -1){
		fprintf(stderr, "Invalid depth size\n");
		exit(1);
	}
	return;
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
	//Fill in with your implementation
	//printf("hello from crawl!\n");
	if(seedURL == NULL || pageDirectory == NULL){
		fprintf(stderr,"Invalid parameters\n");
		exit(1);
	}

	int ID = 0;
	
	
	//initialize webpage that represents seedURL at depth 0
	webpage_t *url_holder = (webpage_t*)malloc(sizeof(webpage_t));
	if(url_holder == NULL){
		fprintf(stderr, "Memory allocation failed\n");
	}
	url_holder->url = strdup(seedURL);
	url_holder->depth = 0;
	url_holder->length = 0;
	
	
	//initialize hashtable and added seedURL
	hashtable_t *ht = hashtable_new(maxDepth);
	hashtable_insert(ht,url_holder->url,0);
	
	//initialize bag that has webpage representing seedURL
	bag_t *bag = bag_new();
	bag_insert(bag,url_holder);
	
	//while bag is not empty
	while(bag->size > 0){
		char *html;
		webpage_t *temp;  

		temp = bag_pull(bag);
	
		html = download(temp->url,&(temp->length));
		//if the fetch was successful
		if(html != NULL){
			temp->html = html;
			ID++;
			pagedir_save(temp,pageDirectory,ID);
			if(temp->depth < maxDepth){
				printf("%d Fetched: %s\n",temp->depth,temp->url);
				printf("%d Scanning: %s\n",temp->depth,temp->url);
				pageScan(temp,bag,ht);
			}
		}
		free(temp->url); //also frees normalized, url_holder->url, and newPage->url
		free(temp->html); //same as free(html)
		free(temp); //should free newPage and temp
	}
	//delete hashtable
	//note: replace with hashtable_delete?
	hashtable_delete(ht);
	//delete bag
	free(bag);
	//free(url_holder);
	
}

/**
 * Scans a webpage for URLs.
 */
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
	//printf("hello from pageScan!\n");
	// Fill in with your implementation
	char* start = "<a href=\"";

	//strstr returns a pointer to the first instance of "start" in html
	//returns a null pointer if not found
	char* first = strstr(page->html,start);
	char* second;
	size_t length;
	int pdepth = page->depth;
	int *pointer = &pdepth;
	
	//conditions to check if parameters are NULL
	if(page == NULL || pagesToCrawl == NULL || pagesSeen == NULL){
		fprintf(stderr,"Invalid parameter\n");
		exit(1);
	}
	
	//condition checks if the html still has a URL
	while(first != NULL){
		char* normalized;
		char* URL;
		//printf("made it past first NULL check in pageScan!\n");
		//moves the pointer to the end of the "start" pattern
		first = first + 9;
		//first = first + 6;
		//finds the first instance of end pattern
		second = strstr(first,"\"");
		//if a URL is found
		if(first != NULL && second != NULL){
			//printf("made it past second NULL check in pageScan!\n");
		//Next two lines finds URL
		//code from https://stackoverflow.com/questions/69735716/how-do-i-print-a-string-between-two-pointers
		//second and first are pointers that point to the beginning and end of URL
			length = second - first + 1;
			URL = strndup(first,length);
			
			normalized = normalizeURL(page->url,URL);
			if(normalized == NULL){
				free(URL);
				continue;
			}

			//printf("in second and first NULL check\n");
		} //pointer in hashtable_insert points to depth of webpage
		if(isInternalURL(page->url,normalized) && hashtable_insert(pagesSeen,URL,pointer) == true){
			webpage_t *newPage = (webpage_t*)malloc(sizeof(webpage_t));
			if(newPage == NULL){
				fprintf(stderr,"Memory allocation failed\n");
			}
			char* html;
			//printf("created newPage\n");
			newPage->url = normalized;
			//printf("set url\n");
			newPage->depth = page->depth + 1;
			//printf("passed newPage\n");
			printf("%d Found: %s\n",newPage->depth,newPage->url);
			
			html = download(normalized,&(newPage->length));
			
			if(html == NULL){
				free(newPage->url);
				free(newPage);
				continue;
			}
			
			newPage->html = html;
			
			bag_insert(pagesToCrawl,newPage);
			printf("%d Added: %s\n",newPage->depth,newPage->url);
			
			free(html);	
		} else{
			free(normalized);
		}
		//finds next occurence of start pattern
		first = strstr(first, start);
		free(URL);
	}
}

int main(const int argc, char *argv[]) {
	// Fill in with your implementation
	//printf("hello from the beginning!\n");
	if(argc != 4){
		fprintf(stderr,"Invalid number of arguments\n");
		exit(1);
	}
	//printf("-----argc check passed!\n");
	char *a = argv[1];
	char **aa = &a;
	char *b = argv[2];
	char **bb = &b;
	int c = atoi(argv[3]);
	int *cPointer = &c;
	
	char *d = argv[1];
	char *e = argv[2];
	//printf("-----starting parseArgs!\n");
	parseArgs(argc,argv,aa,bb,cPointer);
	//printf("-----starting crawl!\n");
	crawl(d,e,c);
	//printf("finished main!\n");
	exit(0);
}
