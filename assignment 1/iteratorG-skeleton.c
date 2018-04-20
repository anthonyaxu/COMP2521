/* iteratorG.c
   Generic Iterator implementation, using doubly linked list

   Written by: ....
   Date: ....

    You need to submit ONLY this file.... 

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "iteratorG.h"

typedef struct Node {

  // implement struct here .. 

} Node;

typedef struct IteratorGRep {

  // implement struct here .. 

} IteratorGRep;


/*
  Your  functions below .... 
 */


IteratorG newIterator(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp){
	// implement function here and change return value 
	return NULL;
}

int  add(IteratorG it, void *vp){
	// implement function here and change return value 
	return 0;
}
int  hasNext(IteratorG it){
	// implement function here and change return value 
	return 0;
}
int  hasPrevious(IteratorG it){
	// implement function here and change return value 
	return 0;
}
void *next(IteratorG it){
	// implement function here 
	return NULL;
}
void *previous(IteratorG it){
	// implement function here  
	return NULL;
}
int  del(IteratorG it){
	// implement function here and change return value 
	return 0;
}
int  set(IteratorG it, void *vp){
	// implement function here and change return value 
	return 0;
}
IteratorG advance(IteratorG it, int n){
	// implement function here and change return value 
	return NULL;
}
void reverse(IteratorG it){
	// implement function here  
	return;
}
IteratorG find(IteratorG it, int (*fp) (void *vp) ){
	// implement function here and change return value 
	return NULL;
}
int distanceFromStart(IteratorG it){
	// implement function here and change return value 
	return 0;
}
int distanceToEnd(IteratorG it){
	// implement function here and change return value 
	return 0;
}
void reset(IteratorG it){
	// implement function here  
	return;
}
void freeIt(IteratorG it){
	// implement function here  
	return;
}



// --------------------------------------





