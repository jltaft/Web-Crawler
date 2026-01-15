#include "pagedir.h"
#include "crawler.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool pagedir_init(const char *pageDirectory) {
	// Fill in with your implementation
	//printf("hello from pd_init!\n");
	
	if(pageDirectory == NULL){
		return false;
	}
	
	FILE *fptr;
	char filePath[50];
	strcpy(filePath,pageDirectory);
	strcat(filePath,"/.crawler");
	fptr = fopen(filePath,"w");
	
	//if fopen failed, then the directory does not exist
	if(fptr == NULL){
		return false;
	} else{
		return true;
	}
	
}

void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
	// Fill in with your implementation
	//printf("hello from pd_save!\n");
	if(pageDirectory == NULL || page == NULL || documentID <= 0){
		fprintf(stderr,"Invalid parameter\n");
		exit(1);
	}
	//printf("passed null check in pd_save!\n");
	char fileName[50];
	//converts documentID to a string using sprintf
	sprintf(fileName, "/%d", documentID);
	//printf("passed sprintf in pd_save!\n");
	FILE *fptr = NULL;
	char filePath[50];
	//copies filePath to pageDirectory
	strcpy(filePath,pageDirectory);
	//printf("%s\n",pageDirectory);
	//printf("passed strcpy in pd_save!\n");
	//concatenates filePath and fileName
	strcat(filePath,fileName);
	//printf("%s\n", strcat(filePath,fileName));
	//printf("passed strcat in pd_save!\n");
	//writes in the documentID file + creates documentID file
	fptr = fopen(filePath,"w");
	//This if statement shouldn't really be necessary unless something messed up
	if(fptr == NULL){
		fprintf(stderr,"Invalid file");
		exit(1);
	}
	//printf("passed fopen in pd_save!\n");
	//Writes the information in the file
	if(page == NULL|| page->url == NULL || page->depth < 0 || page->html == NULL){
		fprintf(stderr,"Invalid page\n");
		exit(1);
	}
	//printf("passed NULL checks in pd_save!\n");
	
	/*printf("%s\n",page->url);
	printf("%d\n",page->depth);
	printf("%s\n",page->html);
	printf("made it passed prints!\n"); */
	
	
	fprintf(fptr,"%s\n%d\n%s", page->url, page->depth, page->html);
	//printf("passed fprintf in pd_save!\n");
	//closes the file
	fclose(fptr);
	//printf("finished pd_save!\n");
}

