# Makefile for Generic List Iterator

CC = gcc
CFLAGS = -Wall -Werror -g -std=gnu11 

all : testIteratorG

testIteratorG : testIteratorG.o iteratorG.o  positiveIntType.o stringType.o 
	$(CC) -o testIteratorG testIteratorG.o iteratorG.o positiveIntType.o stringType.o 

testIteratorG.o : testIteratorG.c iteratorG.h positiveIntType.h stringType.h
	$(CC) $(CFLAGS) -c testIteratorG.c

iteratorG.o : iteratorG.c iteratorG.h  

positiveIntType.o : positiveIntType.c positiveIntType.h 
 
stringType.o : stringType.c stringType.h 



clean :
	rm -f *.o testIteratorG core

