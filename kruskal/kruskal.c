#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quickSort.h"

FILE *file; 
int vertices, edges;

edge **readEdges(){
    edge **edgesList = (edge**) malloc(edges * sizeof(edge));
    int i, u, v, weight;
    
    for (i = 0; i < edges; i++){
        fscanf(file, "%d%d%d", &u, &v, &weight);

        edgesList[i] = (edge*) malloc(sizeof(edge*));
        edgesList[i]->u = u;
        edgesList[i]->v = v;
        edgesList[i]->weight = weight;
    }
    return edgesList;
}

vertex **_makeSet(){
    vertex **verticesList = (vertex**) malloc((vertices + 1) * sizeof(vertex));
    int i;
    for (i = 1; i <= vertices; i++){
        verticesList[i] = (vertex*) malloc(sizeof(vertex));
        verticesList[i]->parent = i;
        verticesList[i]->rank = 0;
    }
    return verticesList;
}


void _union(int u, int v, vertex **verticesList){
    int uParent = verticesList[u]->parent, vParent = verticesList[v]->parent; 
    if(verticesList[uParent]->rank >= verticesList[vParent]->rank){
        verticesList[vParent]->parent = uParent;
        if(verticesList[uParent]->rank == verticesList[vParent]->rank) verticesList[uParent]->rank++;
    }
    else verticesList[uParent]->parent = vParent;
}

int _find(int u, vertex **verticesList){
    int parent = verticesList[u]->parent;
    if(parent != u) 
        verticesList[u]->parent = _find(parent, verticesList);

    return verticesList[u]->parent;

}




edge **kruskal(edge **edgesList){
    edge **mst = (edge **) malloc((vertices-1) * sizeof(edge*));
    int mstSize = 0, i;
    vertex **verticesList = _makeSet();

    for (i = 0; i < edges; i++){
        int u = edgesList[i]->u;
        int v = edgesList[i]->v;
        if(_find(u, verticesList) != _find(v, verticesList)){
            // printf("%d\n", mstSize);
            mst[mstSize++] = edgesList[i];
            _union(u, v, verticesList);
            // printf("(%d,%d, %d-%d)\n", u, v, verticesList[u]->parent, verticesList[v]->parent);
        }
    }

    return mst;
}

void main(int argc, char *argv[]){
    int i, root;
    char *fileName = (char*) malloc(30 * sizeof(char));
    char *execCommand = (char*) malloc(5 * sizeof(char));
     for (i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-f")) fileName = argv[++i];
        else if(!strcmp(argv[i], "-i")) root = atoi(argv[++i]);
        else if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "-s")) execCommand = argv[i];
    }
    file = fopen(fileName, "r");
     if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    fscanf(file, "%d%d", &vertices, &edges);

    edge **edgesList = readEdges();
    sort(edgesList, 0, edges);
    // printf("%d %d\n", vertices, edges);
    edge **mst = kruskal(edgesList);
    int count = 0;
    
    char *mstRep = (char*) calloc(vertices * 12, sizeof(char));
    for (i = 0; i < vertices-1; i++){
        char aux[12];
        sprintf(aux, "(%d,%d) ", mst[i]->u, mst[i]->v);
        strcat(mstRep, aux);
        count += mst[i]->weight;
    }
    if(!strcmp(execCommand, "-s")) printf("%s\n", mstRep);
    else if(!strcmp(execCommand, "-h")){}
    else printf("%d\n", count);
}