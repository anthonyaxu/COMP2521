// Graph ADT interface for Ass2 (COMP2521)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Graph.h"

typedef struct GraphRep {

	int nVert;
	AdjList * adjListArray;

} GraphRep;


Graph newGraph(int noNodes) {


	Graph g;
	if((g= malloc(sizeof(GraphRep))) == NULL){
		fprintf(stderr, "Error!!  .... \n");
	}
	g->nVert = noNodes;

	//malloc and init adjList
	if((g->adjListArray = malloc(sizeof(AdjList)*g->nVert)) == NULL){
		fprintf(stderr, "Error!!  .... \n");
	}
	int i = 0;
	while(i<g->nVert){
		g->adjListArray[i] = NULL;
		i++;
	}

	return g;
}

int numVerticies(Graph g) {
	return g->nVert;
}

void  insertEdge(Graph g, Vertex src, Vertex dest, int weight) {

	if (src>g->nVert || dest>g->nVert || src == dest)
		return;
	// check if dest is in g->adjListArray[src]
	AdjList tmp;
	tmp = g->adjListArray[src];
	while(tmp!=NULL){
		if (tmp->w==dest) {
			return;
		}
		tmp = tmp->next;
	}


	// add dest to src
	AdjList new = malloc(sizeof(AdjList));
	new->weight = weight;
	new->w = dest;
	new->next = g->adjListArray[src];
	g->adjListArray[src] = new;


	
}

void  removeEdge(Graph g, Vertex src, Vertex dest) {

	if (src>g->nVert || dest>g->nVert || src == dest)
		return;
	// check if dest is in g->adjListArray[src]
	AdjList tmp;
	tmp = g->adjListArray[src];
	while(tmp!=NULL){
		if (tmp->w==dest) {
			//found connecton from v to w


			//deleting from g->adjListArray[src]
			if(tmp->next==NULL && tmp!=g->adjListArray[src]){
				AdjList tmp2 = g->adjListArray[src]; 
				while (tmp2->next!=tmp){
					tmp2 = tmp2->next;
				}
				//tmp2 pointing before tmp in adjlist
				tmp2->next = NULL;
				free(tmp);
			} else if (tmp==g->adjListArray[src] && tmp->next==NULL) {
				g->adjListArray[src] = NULL;
				free(tmp);
			} else if (tmp==g->adjListArray[src]) {
				g->adjListArray[src] = tmp->next;
				free(tmp);
			} else {
				AdjList tmp2 = g->adjListArray[src];
				while (tmp2->next!=tmp){
					tmp2 = tmp2->next;
				}
				//tmp2 pointing before tmp in adjlist
				tmp2->next = tmp->next;
				free(tmp);
			}

			printf("deleted\n");
			return;
		}
		tmp = tmp->next;
	}
	printf("nothing deleted\n");

}

bool adjacent(Graph g, Vertex src, Vertex dest) {

	AdjList tmp = g->adjListArray[src];
	while(tmp!=NULL){
		if (tmp->w==dest) {
			printf("FOUND");
			return true;
		}
		tmp = tmp->next;
	}


	return false;
}

AdjList outIncident(Graph g, Vertex v) {
	return g->adjListArray[v];
}

AdjList inIncident(Graph g, Vertex v) {

	int i = 0;
	AdjList list = NULL;
	AdjList head = NULL;
	AdjList new;
	AdjList tmp;
	while(i < g->nVert) {
		tmp = g->adjListArray[i];
		while(tmp!=NULL) {
			if (tmp->w==v) {
				if (list == NULL) {
					new = malloc(sizeof(AdjList));
					new->weight = tmp->weight;
					new->w = i;
					new->next = NULL;
					list = new;
					head = new;
				} else {
					new = malloc(sizeof(AdjList));
					new->weight = tmp->weight;
					new->w = i;
					list->next = new;
					list = list->next;
					new->next = NULL;
				}
			}
			tmp = tmp->next;
		}
		i++;
	}

	AdjList ret = head;
	while(ret!=NULL) {
		ret = ret->next;
	}
	return head;
}

void  showGraph(Graph g) {

	int i = 0;
	while(i < g->nVert) {
		AdjList tmp = g->adjListArray[i];
		printf("\n || %d ||",i);
		while(tmp!=NULL){
			printf("---> { %d } ",tmp->w);
			tmp = tmp->next;
		}
		printf(" ---> NULL\n");

		i++;
	}
	printf("\n");

}

void  freeGraph(Graph g) {
	int i = 0;
	while(i < g->nVert) {
		AdjList tmp = g->adjListArray[i];
		while(tmp!=NULL){
			AdjList del = tmp;
			free(del);
			tmp = tmp->next;
		}
		i++;
	}
	free(g);


}