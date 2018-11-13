// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct PQRep {
	int index;
	int size;
	ItemPQ *item;
} PQRep;

int getRightChild(int id) {
	return 2*id + 1;
}

int getLeftChild(int id) {
	return 2*id;
}

int getParent(int id) {
	return id/2;
}

int PQEmpty(PQ pq) {
	return (pq->index == 0);
}

void swapItems(PQ pq, int id1, int id2) {
	ItemPQ tmp = pq->item[id1];
	pq->item[id1] = pq->item[id2];
	pq->item[id2] = tmp; 
}

void shiftUp(PQ pq, int id) {
	while (id != 1) {
		int parent = getParent(id);
		// if child is greater than the parent, do nothing
		if (pq->item[id].value > pq->item[parent].value) {
			break;
		} else {
			// swap parent and child item
			swapItems(pq, id, parent);
		}
		id = parent;
	}
}

// not yet
void shiftDown(PQ pq, int id) {
	int left_child;
	int right_child;
	int parent;
	int swapChild;
	int breakLoop = 0;
	while(true) {
		// printf("whatasdasd??\n");
		left_child = getLeftChild(id);
		right_child = getRightChild(id);
		parent = id;
		if (right_child > pq->index) {
			if (left_child > pq->index) {
				break;
			}
			swapChild = left_child;
			breakLoop = 1;
		} else if (pq->item[left_child].value < pq->item[right_child].value) {  // check which child is smallest
			swapChild = left_child; 
		} else {
			swapChild = right_child;
		}
		// if child is smaller than parent
		if (pq->item[parent].value > pq->item[swapChild].value) {
			swapItems(pq, parent, swapChild);
			id = swapChild;
		} else {
			break;
		}
		if (breakLoop == 1) {
			break;
		}
	}
}

int getItemID(PQ pq, ItemPQ element) {
	for (int id = 1; id <= pq->index; id++) {
		if (pq->item[id].key == element.key) {
			return id;
		}
	}
	return -1;
}

int checkKey(PQ pq, ItemPQ element) {
	for (int id = 1; id <= pq->index; id++) {
		if (pq->item[id].key == element.key) {
			return 0;
		}
	}
	return 1;
}

PQ newPQ() {
	PQ pq;
	if ((pq = malloc(sizeof(PQ))) == NULL) {
		fprintf(stderr, "Error!\n");
	}
	// index to malloc memory
	int initial_size = 3;
	pq->item = malloc(sizeof(ItemPQ)*(initial_size + 1));
	pq->index = 0;
	pq->size = initial_size;
	return pq;
}

void addPQ(PQ pq, ItemPQ element) {
	int check = checkKey(pq, element);
	if (check == 0) {
		// if added item's key already exists
		updatePQ(pq, element);
	} else {
		int id = pq->index + 1;
		if (id == pq->size) {
			pq->size = 2*pq->size;
			pq->item = realloc(pq->item, sizeof(ItemPQ)*pq->size);
		}
		pq->item[id] = element;
		pq->index++;
		if (pq->index > 1) {
			shiftUp(pq, id);
		}	
	}
}

ItemPQ dequeuePQ(PQ pq) {
	ItemPQ returned = pq->item[1];
	pq->item[1] = pq->item[pq->index];
	pq->index--;
	// make sure there is something in the queue when shifting down
	if (pq->index > 0) {
		shiftDown(pq, 1);
	}
	return returned;
}

void updatePQ(PQ pq, ItemPQ element) {
	int id = getItemID(pq, element);
	if (id == -1) {
		printf("ITEM IS NOT INSIDE QUEUE\n");
		exit(1);
	} else {
		pq->item[id].value = element.value;
		int parent = getParent(id);
		int left_child = getLeftChild(id);
		int right_child = getRightChild(id);
		// if element is at bottom/end
		if ((left_child > pq->index) && (right_child > pq->index)) {
			// then check if element is less than element
			if (pq->item[id].value < pq->item[parent].value) {
				// probably don't need above if statement. shiftUp does the check
				shiftUp(pq, id);
			}
		// if element is the first one
		} else if (id == 1) {
			shiftDown(pq, id);
		} else if (pq->item[id].value > pq->item[parent].value) {		// check if element is greater than parent
			shiftDown(pq, id);
		} else {						// else if element is smaller than children
			shiftUp(pq, id);
		}
	}
}

void  showPQ(PQ pq) {
    for (int i = 1; i <= pq->index; i++) {
        printf("| key: %d | value: %d |\n",pq->item[i].key, pq->item[i].value);
    }
    printf("\n");
}

void  freePQ(PQ pq) {
	free(pq->item);
	free(pq);
}
