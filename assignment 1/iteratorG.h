/** iteratorG.h ... interface to generic Iterator
    Written by Ashesh Mahidadia, March 2018

    See the assignment specifications for the required functionality of 
    the following functions. 
**/

#ifndef LISTITERATORG_H
#define LISTITERATORG_H

#include <stdio.h>

typedef struct IteratorGRep *IteratorG;

typedef int   (*ElmCompareFp)(void const *e1, void const *e2);
typedef void *(*ElmNewFp)(void const *e1);
typedef void  (*ElmFreeFp)(void *e1);


IteratorG newIterator(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp);
int  add(IteratorG it, void *vp);
int  hasNext(IteratorG it);
int  hasPrevious(IteratorG it);
void *next(IteratorG it);
void *previous(IteratorG it);
int  del(IteratorG it);
int  set(IteratorG it, void *vp);
IteratorG advance(IteratorG it, int n);
void reverse(IteratorG it);
IteratorG find(IteratorG it, int (*fp) (void *vp) );
int distanceFromStart(IteratorG it);
int distanceToEnd(IteratorG it);
void reset(IteratorG it);
void freeIt(IteratorG it);

#endif
