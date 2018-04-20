/*
  testIteratorG.c 
  Client to test Generic Iterator 
  
  Written by: ....
  Date: ....
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "iteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

#define MAXARRAY 5

int main(int argc, char *argv[])
{
  
  /* The following code, inside the comments, may or may not be correct!
     
     It's provided in case you find it difficult to understand 
     how to create a generic iterator, and use it's functions.
     
     Please study SetG example we discussed in the lecture in detail.

     The code below only tests basic operations, however 
     make sure that you do test all the required functions properly in
     your test file. 

  */
  
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */
  
/*
  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntNew, positiveIntFree);
  
  int a[MAXARRAY] = { 25, 12, 6, 82 , 11};
  
  int i;
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
*/	
	/*
	The above loop should print ... 
		Inserting 25: Success 
		Inserting 12: Success 
		Inserting 6: Success 
		Inserting 82: Success 
		Inserting 11: Success
	*/  

/*
  int *v1 = (int *) next(it1);
  printf("Next value is: %d \n", *v1 );  // should print "Next value is: 11" 
  
  int *v2 = (int *) next(it1);
  printf("Next value is: %d \n", *v2 );  // should print "Next value is: 82" 
  
  int *v3 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v3 );     // should print "Previous value is: 82" 
*/  

  /* =======================================
     --------- stringType List Iterator ----------
  */
 
/* 
  IteratorG it2 = IteratorGNew(stringCompare, stringNew, stringFree);
  
  char *strA[MAXARRAY];
  strA[0] = strdup("john");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby"); 
  
  int j;
  for(j=0; j<4; j++){
    int result = add(it2 , strA[j]); 
    printf("Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }
*/
	/*
	The above loop should print ... 
		Inserting john: Success 
		Inserting rita: Success 
		Inserting john: Success 
		Inserting abby: Success
	*/
/*
  char *v4 = (char *) next(it2);
  printf("Next value is: %s \n", v4 );  // should print: "Next value is: abby"
  
  char *v5 = (char *) next(it2);
  printf("Next value is: %s \n", v5 );  // should print: "Next value is: john"
  
  char *v6 = (char *) previous(it2);
  printf("Previous value is: %s \n", v6 );      // should print: "Previous value is: john"
  
*/
  return EXIT_SUCCESS;
  
}
