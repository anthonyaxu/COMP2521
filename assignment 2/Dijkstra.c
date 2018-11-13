// Dijkstra ADT interface for Ass2 (COMP2521)
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#define INFINITY 99999

ShortestPaths init(Graph g, Vertex v);

ShortestPaths dijkstra(Graph g, Vertex v) {

	ShortestPaths sp = init(g,v);

	PQ pq = newPQ();
    ItemPQ new;
	for (int i = 0; i < sp.noNodes; i++) {
		if (i!=v) {
			sp.dist[i] = INFINITY;
			new.key = i;
			new.value = INFINITY;
			addPQ(pq, new);
		}
		sp.pred[i] = NULL;
	}
	sp.dist[v] = 0;
	new.key = v;
	new.value = 0;
	addPQ(pq, new);
	int newDist;
	ItemPQ item;
	while (PQEmpty(pq)==0) {
		item = dequeuePQ(pq);
		int src = item.key;
		AdjList verts = outIncident(g, src);
		while(verts!=NULL){
			int dest = verts->w;
			newDist = sp.dist[src] + verts->weight;
			if (newDist <= sp.dist[dest]) {
				PredNode *new = malloc(sizeof(PredNode));
				new->v = src;
				new->next = NULL;
				if (newDist == sp.dist[dest] && sp.pred[dest]!=NULL) {
					PredNode *tmp = sp.pred[dest];
					while(tmp->next!=NULL){
						tmp = tmp->next;
					}
					tmp->next = new;
				} else {
					sp.pred[dest] = new;
				}

				item.key = dest;
				item.value = newDist;
				updatePQ(pq, item);
				sp.dist[dest] = newDist;
			}
			verts = verts->next;
		}
	}

	for (int i = 0; i < sp.noNodes; i++) {
		if (sp.dist[i] == INFINITY) {
			sp.dist[i] = 0;
		}
	}

	return sp;
}

void showShortestPaths(ShortestPaths paths) {

	int i = 0;
	printf("Node %d\n",paths.src);
	printf("  Distance\n");
	for (i = 0; i < paths.noNodes; i++) {
			if(i == paths.src)
	    	printf("    %d : X\n",i);
			else
				printf("    %d : %d\n",i,paths.dist[i]);
	}
	printf("  Preds\n");
	for (i = 0; i < paths.noNodes; i++) {
		printf("    %d : ",i);
		PredNode* curr = paths.pred[i];
		while(curr!=NULL) {
			printf("[%d]->",curr->v);
			curr = curr->next;
		}
		printf("NULL\n");
	}


}


void  freeShortestPaths(ShortestPaths paths) {

}

ShortestPaths init(Graph g, Vertex v) {
	ShortestPaths *sp = malloc(sizeof(ShortestPaths));
	sp->src = v;
	sp->noNodes = numVerticies(g);
	sp->dist = malloc(sizeof(int)*numVerticies(g));
	sp->pred = malloc(sizeof(PredNode)*numVerticies(g));
	return *sp;
}