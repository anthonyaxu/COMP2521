// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

int main(int argc, char *argv[])
{
    DLList myList;
    myList = getDLList(stdin);
	
    printf("-------------------------\n");
		
    printf("List inputed:\n");
    putDLList(stdout,myList);
    assert(validDLList(myList));
	
    //printf("curr = %s\n", DLListCurrent(myList));
    printf("nitems = %d\n", DLListLength(myList));
	
    printf("-------------------------\n");
	
    printf("Add new value before current line\n");
    printf("List:\n");
    DLListBefore(myList, "before");
    putDLList(stdout, myList);
    assert(validDLList(myList));

    //printf("curr = %s\n", DLListCurrent(myList));
    printf("nitems = %d\n", DLListLength(myList));
	
    printf("-------------------------\n");
	
    printf("Add new value after current line\n");
    printf("List:\n");
    DLListAfter(myList, "after");
    putDLList(stdout, myList);
    assert(validDLList(myList));
    
    //printf("curr = %s\n", DLListCurrent(myList));
    printf("nitems = %d\n", DLListLength(myList));
    
    printf("-------------------------\n");
    
    printf("Delete current line\n");
    printf("List:\n");
    DLListDelete(myList);
    putDLList(stdout, myList);
    assert(validDLList(myList));
    
    printf("nitems = %d\n", DLListLength(myList));

	
	return 0;
}
