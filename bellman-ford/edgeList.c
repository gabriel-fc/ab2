#include <stdio.h>
#include <stdlib.h>
#include "edgeList.h"


edge *createEdge(int u, int v, int weight){
    edge *uv = (edge*) malloc(sizeof(edge));
    uv->u = u;
    uv->v = v;
    uv->weight = weight;
    return uv;
}


edge **readEdgeList(int edges, FILE *f){
    edge **list = (edge**) malloc(sizeof(edge*) * edges);
    int i, u, v, weight;
    for (i = 0; i < edges; i++){
        fscanf(f, "%d%d%d", &u, &v, &weight);
        list[i] = createEdge(u,v,weight);
    }
    return list;
}

void freeEdgeList(int edges, edge **edgeList){
    int i, j;
    for (i = 0; i < edges; i++){
        free(edgeList[i]);
    }
    free(edgeList);
    
}







