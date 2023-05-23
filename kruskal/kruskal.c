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

vertex **setVerticesList(){
    vertex **verticesList = (vertex**) malloc((vertices + 1) * sizeof(vertex));
    int i;
    for (i = 1; i <= vertices; i++){
        verticesList[i] = (vertex*) malloc(sizeof(vertex));
        verticesList[i]->parent = i;
        verticesList[i]->rank = 0;
    }
    return verticesList;
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

    
}