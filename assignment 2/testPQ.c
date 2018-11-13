#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    PQ pq = newPQ();
    ItemPQ new;
    new.key = 0;
    new.value = 9999;
    printf("Adding k: %d  v: %d\n",new.key,new.value);
    addPQ(pq,new);
    showPQ(pq);

    new.key = 1;
    new.value = 2;
    printf("Adding k: %d  v: %d\n",new.key,new.value);
    addPQ(pq,new);
    showPQ(pq);

    new.key = 8;
    new.value = 5;
    printf("Adding k: %d  v: %d\n",new.key,new.value);
    addPQ(pq,new);
    showPQ(pq);

    new.key = 12;
    new.value = 8;
    printf("Adding k: %d  v: %d\n",new.key,new.value);
    addPQ(pq,new);
    showPQ(pq);

    new.key = 2;
    new.value = 9999;
    printf("Adding k: %d  v: %d\n",new.key,new.value);
    addPQ(pq,new);
    showPQ(pq);

    new.key = 3;
    new.value = 9999;
    printf("Adding k: %d  v: %d\n",new.key,new.value);
    addPQ(pq,new);
    showPQ(pq);

    new.key = 3;
    new.value = 10;
    printf("Adding k: %d  v: %d\n",new.key,new.value);
    addPQ(pq,new);
    showPQ(pq);

    new.key = 1;
    new.value = 69;
    printf("updating k: %d with v: %d\n",new.key,new.value);
    updatePQ(pq,new);
    showPQ(pq);

    ItemPQ removed;
    removed = dequeuePQ(pq);
    printf("Dequeued: k:%d v:%d\n",removed.key,removed.value);
    showPQ(pq);

    removed = dequeuePQ(pq);
    printf("Dequeued: k:%d v:%d\n",removed.key,removed.value);
    showPQ(pq);

    removed = dequeuePQ(pq);
    printf("Dequeued: k:%d v:%d\n",removed.key,removed.value);
    showPQ(pq);

    removed = dequeuePQ(pq);
    printf("Dequeued: k:%d v:%d\n",removed.key,removed.value);
    showPQ(pq);

    removed = dequeuePQ(pq);
    printf("Dequeued: k:%d v:%d\n",removed.key,removed.value);
    showPQ(pq);


    return 0;
}
