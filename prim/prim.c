#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "inputHandler.h"






qElement **prim(int root, int vertices, qList *q, adjList **adjLists){
    int i;
    qElement **mst = (qElement**) malloc(vertices*sizeof(qElement));


    while(q->size){
        int mstIndex = vertices - q->size;
        qElement *u = pop(q);
        adjVertex *v = adjLists[u->vertex]->head;
        while(v){
            int vIndexAtQ = q->elementPosition[v->vertex]; 
            if(vIndexAtQ != -1 && q->heap[vIndexAtQ]->key  >= v->weight){
                decreaseKey(vIndexAtQ, v->weight, u->vertex, q);
            }
            v = v->next;
        }
        mst[mstIndex] = u;
    }
    return mst;
}

void printMST(qElement **mst, int vertices){
    int i;
    for (i = 1; i < vertices; i++){
        printf("(%d,%d) ", mst[i]->vertex, mst[i]->neighbor);
    }
}

void printCost(qElement **mst, int vertices){
    int i, count = 0;
    for (i = 0; i < vertices; i++){
        count += mst[i]->key; 
    }
    printf("%d\n", count);
}

void main(int argc, char *argv[]){

    int vertices, edges, i, root = 1;
    char *fileName = (char*)malloc(100 * sizeof(char));
    char *execCommand = (char*)malloc(100 * sizeof(char));
    
    for (i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-f")) fileName = argv[++i];
        else if(!strcmp(argv[i], "-i")) root = atoi(argv[++i]);
        else if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "-s")) execCommand = argv[i];
    }
    FILE *file = fopen(fileName, "r");
     if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fscanf(file, "%d%d", &vertices, &edges);
    adjList **adjLists = createAdjLists(file, vertices, edges);
    qList *q = initHeap(vertices, root);
    qElement **mst = prim(root, vertices, q, adjLists);


    if(!strcmp(execCommand, "-s")) printMST(mst, vertices);
    else if(!strcmp(execCommand, "-h")){}
    else printCost(mst, vertices);

    freeLists(adjLists, vertices);
    freeQ(q);
    free(mst);
}
