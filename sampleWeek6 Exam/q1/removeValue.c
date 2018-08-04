// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/



void removeValue(DLList L, int value){

	struct DLListNode *n = L->first;
	struct DLListNode *temp;

	while (n != NULL) {
		if (n->value == value) {
			if (n->next == NULL) {
				temp = n;
				L->first = L->last = L->curr = NULL;
				free(temp);
			} else if (n == L->first) {
				temp = n;
				L->first = n->next;
				free(temp);
			}
		}
		n = n->next;
	}

	return;
}



