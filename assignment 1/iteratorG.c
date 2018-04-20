/*  iteratorG.c
    Generic Iterator implementation, using doubly linked list
	For COMP2521 assignment 1, Semester 1 2018, UNSW
    Written by: Anthony Xu (z5165674)
    Date: 15/04/2018	
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "iteratorG.h"

// ---- Prototypes for functions in iterator ---- //
void  IntFree(void *vp);
void *IntNew(void const *vp);
int   IntCompare(void const *vp1, void const *vp2);
void  freeString(void *vp);
void *newString(void const *vp);
int   compareString(void const *vp1, void const *vp2);
// ---------------------------------------------- //

typedef struct Node {
	void *value; 		  // value of item (string)
	struct Node *prev; 	  // pointer to previous node in list
	struct Node *next; 	  // pointer to next node in list
} Node;

typedef struct IteratorGRep {
    int nitems; 		  // count of items in list
	Node *first; 		  // first node in list
	Node *last;  		  // last node in list
	Node *cur_prev;		  // node left of iterator
	Node *cur_next;		  // node right of iterator
	Node *recent_return;  // stores most recent returned node

	ElmCompareFp cmpFp;   // function to compare values
	ElmNewFp newFp;       // function to create new values
	ElmFreeFp freeFp;     // function to free values
} IteratorGRep;

// Creates a new generic list iterator with given functions to handle elements
IteratorG newIterator(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp) {

	struct IteratorGRep *L;

	L = malloc(sizeof(struct IteratorGRep));

	assert(L != NULL);

	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->cur_prev = NULL;
	L->cur_next = NULL;
	L->recent_return = NULL;

	L->cmpFp = cmpFp;
	L->newFp = newFp;
	L->freeFp = freeFp;

	return L;
}

// Inserts the specified element pointed by 'vp' into the list iterator 'it'
int add(IteratorG it, void *vp) {
	 
	assert(it != NULL);

	struct Node *new;

	// return 0 if malloc fails to add
	if ((new = malloc(sizeof(Node))) == NULL) {
		return 0;
	}
	new->value = it->newFp(vp);

	if (it->first == NULL) {				// if list is empty
		it->first = it->last = it->cur_next = new;
		it->cur_prev = NULL;
	} else if (it->cur_prev == NULL) {		// cursor is at very left of list
		it->first = new;
		new->next = it->cur_next;
		it->cur_next->prev = new;
		it->cur_next = new;
	} else if (it->cur_next == NULL) {		// cursor is at very right of list
		it->last = new;
		it->cur_next = new;
		new->next = NULL;
		it->cur_prev->next = new;
		new->prev = it->cur_prev;
		it->cur_next = new;
	} else {								// cursor is between two values
		new->next = it->cur_next;
		it->cur_next->prev = new;
		it->cur_prev->next = new;
		new->prev = it->cur_prev;
		it->cur_next = new;
	}
	it->nitems++;
	it->recent_return = NULL;
	return 1;
}

// Returns 1 if the given list iterator has more elements when traversing the list in the forward direction, returns 0 otherwise
int hasNext(IteratorG it) {

	//assert(it != NULL);
	if (it == NULL) {
	    return 0;
	}
	it->recent_return = NULL;
	if (it->cur_next == NULL) {         // if cursor is at end, return 0
		return 0;
	} else {
		return 1;
	}
}

// Returns 1 if the given list iterator has more elements when traversing the list in the reverse direction, returns 0 otherwise
int hasPrevious(IteratorG it) {

	assert(it != NULL);
	
	it->recent_return = NULL;
	if (it->cur_prev == NULL) {         // if cursor is at front, return 0
		return 0;
	} else {
		return 1;
	}

}

// Returns the pointer to the next element in the given list iterator and advances the cursor position
// The method returns NULL if it has no next value
void *next(IteratorG it) {

	if (hasNext(it) == 0) {
		return NULL;
	} else {
	    struct Node *right it->cur_next;
	    struct Node *new_next = right->next;
	   
	    it->recent_return = it->cur_next;
	    it->cur_next = new_next;
	    it->cur_prev = right;

		return it->recent_return;
	}
}

// Returns the pointer to the previous element in the given list iterator and moves the cursor position backwards
// The method returns NULL if it has no previous value
void *previous(IteratorG it){

	if (hasPrevious(it) == 0) {
		return NULL;
	} else {
		struct Node *left = it->cur_prev;
		struct Node *new_prev = left->prev;

		it->cur_next = left;
		it->cur_prev = new_prev;
		it->recent_return = left;

		return it->recent_return;
	}
}

// Removes from the list iterator the previous element, if any
// Returns 1 if successful, 0 otherwise (for example, no previous element to remove)
int del(IteratorG it) {

	assert (it != NULL);

	if (it->cur_prev == NULL) {													// if nothing before cursor
		return 0;
	} else if ((it->first->next == NULL) && (it->cur_prev == it->first)) {		// if there is only one in list
		struct Node *temp;
		temp = it->first;
		it->cur_prev = it->cur_next = it->first = it->last = NULL;
		free(temp);
	} else if (it->cur_prev == it->first) {										// if deleting first element
		struct Node *temp;
		temp = it->first;
		it->first = it->cur_next;
		it->first->prev = NULL;
		it->cur_prev = NULL;
		free(temp);
	} else if (it->cur_prev == it->last) {										// if deleting last element (it->cur_next == NULL)
		struct Node *temp = it->last;
		struct Node *new_last = it->last->prev;
		it->cur_prev = new_last;
		it->last = new_last;
		new_last->next = NULL;
		free(temp);
	} else {
		struct Node *temp;
		struct Node *left = it->cur_prev->prev;
		temp = it->cur_prev;
		left->next = it->cur_next;
		it->cur_next->prev = left;
		it->cur_prev = left;
		free(temp);
	}
	it->nitems--;
	it->recent_return = NULL;
	return 1;
}

// Replaces the 'previous' element with the specified element (*vp), if any
// Returns 1 if successful, 0 otherwise (for example, no previous element)
int set(IteratorG it, void *vp) {
	assert(it != NULL);

	if (it->first == NULL || it->cur_prev == NULL) {		// if list is empty or cursor is at very left
		return 0;
	} else {
		it->cur_prev->value = it->newFp(vp);
	}
	it->recent_return = NULL;
	return 1;
}

// Advances 'it' by 'n' elements. Note that 'n' can be a positive or a negative integer. 
// The function returns a new iterator with 'n' elements, in the same order as they were visited, see examples below. 
// If advancement by 'n' elements is not possible, the function returns 'null' and the cursor position is not changed. 
// The new iterator uses the same functions as used by 'it' to handle elements
IteratorG advance(IteratorG it, int n) {

	assert (it != NULL);
	
	struct IteratorGRep *new_it;
	// check whether it has values that are strings or values
	if (isdigit(it->first->value) == 0) {
	    new_it = newIterator(compareString, newString, freeString);
	} else {
	    new_it = newIterator(IntCompare, IntNew, IntFree);
	}
    
    // Check if moving n places will still be in the list, return NULL if not
    int distanceEnd = distanceToEnd(it);
    int distanceStart = distanceFromStart(it);

    struct Node *node;
    struct Node *tmp;
    struct Node *addNode;
    
    // checks whether n is positive or negative
    if (n >= 0) {
        if (n > distanceEnd) {	// returns NULL if n is greater than the amount of elements available
            return NULL;
        } 
        node = it->cur_next;
        for (int i = 0; i < n; i++) {
            tmp = node;
            addNode = malloc(sizeof(struct Node));				// creates new node to append to new_it
            addNode->value = it->newFp(tmp->value); 			// addNode = element that is passed by cursor
            if (new_it->first == NULL) {            			// if new_it is empty
                new_it->first = new_it->last = new_it->cur_next = addNode;
                new_it->cur_prev = NULL;
                new_it->first->next = NULL;
                new_it->nitems++;
            } else {											// appends addNode to end of new_it
                struct Node *old;
                old = new_it->last;
                new_it->last = addNode;
                new_it->last->prev = old;
                old->next = new_it->last;
                new_it->last->next = NULL;
                new_it->nitems++;
            }
            node = node->next;
        }
        it->cur_next = node;
        if (node == NULL) {										// places cursor between elements where loop has finished
            it->cur_prev = it->last;
        } else {
            it->cur_prev = node->prev;
        }
        free(addNode);
        return new_it;
    } else {
        if (abs(n) > distanceStart) {
            return NULL;
        }
        n = abs(n);												// make n positive (easier to loop)
        node = it->cur_prev;
        for (int i = 0; i < n; i++) {
            tmp = node;
            addNode = malloc(sizeof(struct Node));
            addNode->value = it->newFp(tmp->value);
            if (new_it->first == NULL) {                		// if new_it is empty
                new_it->first = new_it->last = new_it->cur_next = addNode;
                new_it->cur_prev = NULL;
                new_it->first->next = NULL;
                new_it->nitems++;
            } else {											// appends addNode to end of list
                struct Node *old;
                old = new_it->last;
                new_it->last = addNode;
                new_it->last->prev = old;
                old->next = new_it->last;
                new_it->last->next = NULL;
                new_it->nitems++;
            }
            node = node->prev;
        }
        it->cur_prev = node;
        if (node == NULL) {										// places cursor between elements where loop has finished
            it->cur_next = it->first;
        } else {
            it->cur_next = node->next;
        }
        free(addNode);
        return new_it;
    }
}

// Reverses the sequence in 'it'
void reverse(IteratorG it) {

    assert(it != NULL);
    
	struct IteratorGRep *new_it;
	// check whether it has values that are strings or values
	if (isdigit(it->first->value) == 0) {
	    new_it = newIterator(compareString, newString, freeString);
	} else {
	    new_it = newIterator(IntCompare, IntNew, IntFree);
	}

    struct Node *node;
    struct Node *tmp;
    struct Node *addNode;
    
    // checking where cursor is to put it back after reverse is done
    struct Node *org_left = it->cur_prev;
    struct Node *org_right = it->cur_next;    
    // checking index of cursor in list for after reverse is done
    int counter = 0;
    for (node = it->first; node != it->cur_prev; node = node->next) {
        counter++;
    }
    
    // put all nodes into new_it from last to first 
    // Example: it = 1, 2, 3 
    // 			new_it = 3, 2, 1
    for (node = it->last; node != NULL; node = node->prev) {
        tmp = node;
        addNode = malloc(sizeof(struct Node));
        addNode->value = it->newFp(tmp->value);
        if (new_it->first == NULL) {										// if new_it is empty
            new_it->first = new_it->last = new_it->cur_next = addNode;
            new_it->cur_prev = NULL;
            new_it->first->next = NULL;
            new_it->nitems++;
        } else {															// append addNode to end of new_it
            struct Node *old;
            old = new_it->last;
            new_it->last = addNode;
            new_it->last->prev = old;
            old->next = new_it->last;
            new_it->last->next = NULL;
            new_it->nitems++;
        }
    }
    free(addNode);
    
    // copy nodes from new_it into it from first to last
    int done_first = 0;
    for (node = new_it->first; node != NULL; node = node->next) {
        tmp = node;
        if (done_first == 0) {												// if node = new_it->first
            it->first = it->last = it->cur_next = tmp;
            it->first->value = it->newFp(tmp->value);
            done_first = 1;
        } else {
            struct Node *old;
            old = it->last;
            it->last = tmp;
            it->last->value = it->newFp(tmp->value);
            it->last->prev = old;
            old->next = it->last;
        }
    }
    
    // placing cursor into correct position
    if (org_left == NULL) {						// if cursor was originally at very left
        it->cur_next = NULL;					// cursor is now at very right
        it->cur_prev = it->last;
    } else if (org_right == NULL) {				// if cursor was originally at very right
        it->cur_next = it->first;				// cursor is not at very left
        it->cur_prev = NULL;
    } else {									// if cursor was in middle of nodes
        node = it->first;	
        for (int i = 0; i < counter; i++) {		// find index and place cursor
            node = node->next;
        }
        it->cur_next = node;
        it->cur_prev = node->prev;
    }
	return;
}

// The function finds elements, after the current cursor position in 'it', for which the function 'fp' returns 1. 
// All such elements are inserted into a new iterator, and this new iterator is returned. 
// The elements are considered in sequence, from the current cursor position to the end of the iterator
IteratorG find(IteratorG it, int (*fp) (void *vp) ) {

    assert(it != NULL);

	struct IteratorGRep *new_it;
	// check whether it has values that are strings or values
	if (isdigit(it->first->value) == 0) {
	    new_it = newIterator(compareString, newString, freeString);
	} else {
	    new_it = newIterator(IntCompare, IntNew, IntFree);
	}
    
    struct Node *node;
    struct Node *addNode;

    // checking where cursor is to put it back after reverse is done
    struct Node *org_left = it->cur_prev;
    struct Node *org_right = it->cur_next;    
    // checking index of cursor in list for after reverse is done
    int counter = 0;
    for (node = it->first; node != it->cur_prev; node = node->next) {
        counter++;
    }
    
    addNode = malloc(sizeof(struct Node));
    int check;   
    for (node = it->cur_next; node != NULL; node = node->next) {				
        check = fp(node->value);												// calls fp function and passes through node->value
        if (check == 1) {														// fp will return 1 if node->value > "some certain value" in function
            addNode = it->newFp(node->value);
            if (new_it->first == NULL) {                                        // if new_it is empty
                new_it->first = new_it->last = new_it->cur_next = addNode;
                new_it->cur_prev = NULL;
                new_it->first->next = NULL;
                new_it->nitems++;
            } else {															// appends addNode to end of list
                struct Node *old;
                old = new_it->last;
                new_it->last = addNode;
                new_it->last->prev = old;
                old->next = new_it->last;
                new_it->last->next = NULL;
                new_it->nitems++;
            }
        }
    }    

    free(addNode);

    // placing cursor into correct position
    if (org_left == NULL) {						// if cursor was originally at very left
        it->cur_next = NULL;					// cursor is now at very right
        it->cur_prev = it->last;
    } else if (org_right == NULL) {				// if cursor was originally at very right
        it->cur_next = it->first;				// cursor is not at very left
        it->cur_prev = NULL;
    } else {									// if cursor was in middle of nodes
        node = it->first;	
        for (int i = 0; i < counter; i++) {		// find index and place cursor
            node = node->next;
        }
        it->cur_next = node;
        it->cur_prev = node->prev;
    }
    printf("test?\n"); // broken at return?? memory problem??
	return new_it;
}

// Calculates the number of elements before the cursor, and returns the value
int distanceFromStart(IteratorG it) {

	assert(it != NULL);

	if (it->cur_prev == NULL) {													// if cursor is at beginning
		return 0;
	} else if (it->cur_next == NULL) {											// if cursor is at end
		return it->nitems;
	} else {																	// counts elements until start of list
		struct Node *count;
		int counter = 0;
		for(count = it->cur_prev; count != NULL; count = count->prev) {
			counter++;
		}
		return counter;
	}
}

// Calculates the number of elements after the cursor, and returns the value
int distanceToEnd(IteratorG it) {

	assert(it != NULL);

	if (it->cur_prev == NULL) {													// if cursor is at beginning
		return it->nitems;
	} else if (it->cur_next == NULL) {											// if cursor is at end
		return 0;
	} else {																	// counts elements until end of list
		struct Node *count;
		int counter = 0;
		for(count = it->cur_next; count != NULL; count = count->next) {		 	
			counter++;
		}
		return counter;
	}
}

// Resets 'it' to the start of the list
void reset(IteratorG it) {
	assert(it != NULL);
	it->cur_next = it->first;
	it->cur_prev = NULL;
	return;
}

// Removes all the nodes in 'it' and frees associated memory
void freeIt(IteratorG it) {
	assert(it != NULL);
	for(it->cur_prev = it->first; it->cur_prev != NULL; it->cur_prev = it->cur_prev->next) {
		struct Node *temp = it->cur_prev;
		it->freeFp(it->cur_prev->value);
		free(temp);
	}
	free(it);
	return;
}

// ----- Functions if values in node are integers ----- //
// Taken from positiveIntType.c
// positiveIntType functions for generic ADT, implementation 
// Written by Ashesh Mahidadia, August 2017
void IntFree(void *vp){
  free(vp);
}

void *IntNew(void const *vp){
  int v = * (int *) vp ;
  
  int *ip = malloc(sizeof(int));
  *ip = v;
  return ip;
}

int IntCompare(void const *vp1, void const *vp2){
  int v1 = * (int *) vp1 ;
  int v2 = * (int *) vp2 ;
  
  if( v1 == v2 ){ return 0; }
  if( v1 < v2 ) { return -1; }
  return 1;
}
// --------------------------------------------------- //

// ----- Functions if values in node are strings ----- //
// Taken from stringType.c
// stringType functions for generic ADT, implementation 
// Written by Ashesh Mahidadia, August 2017
void freeString(void *vp){
  free(vp);
}

void *newString(void const *vp){
  return strdup(vp);
}

int compareString(void const *vp1, void const *vp2){
  return strcmp(vp1, vp2);
}
// --------------------------------------------------- //