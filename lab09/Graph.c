// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

#define CITY_NUMBER 30

int nextVertex(Graph, Vertex, Vertex, int);

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL);

	Vertex start = src;
	Vertex end = dest;
	int index = 1;

	if (start == end) {
		path[0] = src;
		return 1;
	}
	path[0] = src;

	while (start != end) {	
		if ((start = nextVertex(g, start, end, max)) != -1) {
			path[index] = start;
			index++;
		} else {
			return 0;
		}
	}

	path[index] = dest;
	return index;
}

int nextVertex(Graph g, Vertex src, Vertex dest, int max) {
	if (src == dest) {
		return 0;
	}

	Vertex start = dest;
	Vertex end = src;

	Queue q = newQueue();
	QueueJoin(q, start);
	int seen[CITY_NUMBER] = {0};

	while (!QueueIsEmpty(q)) {
		Vertex cur_vert = QueueLeave(q);
		seen[cur_vert] = 1;
		for (Vertex cur_next = 0; cur_next < CITY_NUMBER; cur_next++) {
			if ((g->edges[cur_vert][cur_next] < max) && (g->edges[cur_vert][cur_next]) != 0) {
				if (seen[cur_next] == 1) {
					continue;
				}
				if (cur_next == end) {
					return cur_vert;
				} else {
					QueueJoin(q, cur_next);
					seen[cur_next] = 1;
				}
			}
		}
	}
	return -1;
}