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

        edgesList[i] = (edge*) malloc(sizeof(edge));
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
    if(verticesList[u]->rank >= verticesList[v]->rank){
        verticesList[v]->parent = u;
        if(verticesList[u]->rank == verticesList[v]->rank) verticesList[u]->rank++;
    }
    
    else verticesList[u]->parent = v;
}

int _find(int u, vertex **verticesList){
    int parent = verticesList[u]->parent;
    if(parent != u) verticesList[u]->parent = _find(parent, verticesList);

    return verticesList[u]->parent;

}




void kruskal(edge **edgesList){
    edge **mst = (edge **) malloc((vertices) * sizeof(edge));
    int mstSize = 0, i;
    vertex **verticesList = _makeSet();

    for (i = 0; i < edges; i++){
        int u = edgesList[i]->u;
        int v = edgesList[i]->v;
        if(_find(u, verticesList) != _find(v, verticesList)){
            // mst[mstSize++] = edgesList[i];
            printf("(%d,%d)\n", u, v);
            _union(u, v, verticesList);
        }
    }

    printf("end\n");
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
    for (i = 0; i < edges; i++){
        printf("%d %d %d\n", edgesList[i]->u, edgesList[i]->v, edgesList[i]->weight);
    }
    
    kruskal(edgesList);
    printf("end");

}