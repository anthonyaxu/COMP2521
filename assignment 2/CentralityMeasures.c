// Graph ADT interface for Ass2 (COMP2521)
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

//double getNumPaths(ShortestPaths paths, double ***passes, int start, int cur, int end);

NodeValues outDegreeCentrality(Graph g){

	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	int count;
	for (int i = 0; i < numVerticies(g); i++)
	{
		count = 0;
		AdjList out = outIncident(g,i);
		while(out!=NULL) {
			count++;
			out = out->next;
		}
		values->values[i] = count;
	}
	return *values;
}
NodeValues inDegreeCentrality(Graph g){
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	int count;
	for (int i = 0; i < numVerticies(g); i++)
	{
		count = 0;
		AdjList out = inIncident(g,i);
		while(out!=NULL) {
			count++;
			out = out->next;
		}
		values->values[i] = count;
	}
	return *values;
}
NodeValues degreeCentrality(Graph g) {
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	NodeValues in = inDegreeCentrality(g);
	NodeValues out = outDegreeCentrality(g);
	for (int i = 0; i < in.noNodes; i++)
	{
		values->values[i] = in.values[i] + out.values[i];
	}
	return *values;
}

NodeValues closenessCentrality(Graph g){
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	values->values = malloc(sizeof(double)*numVerticies(g));
	double count;
	double N = numVerticies(g);
	double n;
	for (int i = 0; i < N; i++)
	{
		count = 0;
		n = 0;
		ShortestPaths paths = dijkstra(g, i);
		for (int j = 0; j < N; j++)
		{
			if (i!=j) {
				count = count + paths.dist[j];
				if (paths.pred[j]!=NULL)
					n++;
			}
		}
		if (n==0) {
			values->values[i] = 0;
		} else {
			values->values[i] = ((n)/(N-1))*((n)/count);
		}
	}
	return *values;
}

double getNumPaths(ShortestPaths paths, double ***passes, int start, int cur, int end){

	if (cur == start) {return 1;}


	double numPaths = 0;
	PredNode *curNode = paths.pred[cur];
	while (curNode) {
		//printf ("Start: %d End: %d Cur: %d CurNode.v: %d\n",start,end, cur,curNode->v);
		numPaths += getNumPaths(paths,passes,start,curNode->v,end);
		curNode = curNode->next;
	}
	if (cur!=end){
		//printf("%lf\n",numPaths);
		passes[start][end][cur] += numPaths;
	}
	return numPaths;
}

NodeValues betweennessCentrality(Graph g){
	NodeValues *values = malloc(sizeof(NodeValues));
	values->noNodes = numVerticies(g);
	int nV = numVerticies(g);
	values->values = malloc(sizeof(double)*(nV+5));

	double ***passes = malloc(sizeof(double**)*(nV+5));
	double **numPaths = malloc(sizeof(double*)*(nV + 5));
	for (int i = 0; i < nV; ++i)
	{
		passes[i] = malloc(sizeof(double*)*(nV+5));
		numPaths[i] =  malloc(sizeof(double)*(nV+5));
		for (int j = 0; j < nV; ++j)
		{
			numPaths[i][j] = 0;
			passes[i][j] = malloc(sizeof(double)*(nV+5));
			for (int k = 0; k < numVerticies(g); ++k)
			{
				passes[i][j][k] = 0;
			}
		}
	}
 	ShortestPaths path;
	for (int start = 0; start < numVerticies(g); start++) {
		path = dijkstra(g, start);
		for (int end = 0; end < numVerticies(g); end++)
		{
			if (start == end) continue;
			numPaths[start][end] = getNumPaths(path, passes, start, end, end);
		}
	}

	for (int start = 0; start < numVerticies(g); start++)
	{
		for (int end = 0; end < numVerticies(g); end++)
		{
			for (int cur = 0; cur < numVerticies(g); cur++)
			{
				if (cur==start|| cur==end) continue;
				//printf("Start: %d End: %d Cur: %d Passes: %lf Paths: %lf\n",start,end,cur,passes[start][end][cur],numPaths[start][end]);
				values->values[cur] += (numPaths[start][end] == 0) ? 0 : (passes[start][end][cur]/numPaths[start][end]);			
			}
		}
	}


	return *values;
}

NodeValues betweennessCentralityNormalised(Graph g){
	NodeValues values = betweennessCentrality(g);
	double n = numVerticies(g);
	for (int i = 0; i < numVerticies(g); i++) {

		values.values[i] = values.values[i]*(1/((n-1)*(n-2)));


	}
	return values;
}

void showNodeValues(NodeValues values){

	for (int i = 0; i < values.noNodes; i++)
	{
		printf("%d: %lf\n",i,values.values[i]);
	}

}

void freeNodeValues(NodeValues values){

}
