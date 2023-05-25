#ifndef EDGE_LIST_H
#define EDGE_LIST_H

typedef struct edge{
    int u;
    int v;
    int weight;
} edge;


edge **readEdgeList(int edges, FILE *f);

void freeEdgeList(int edges, edge **edgeList);



#endif