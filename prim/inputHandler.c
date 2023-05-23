#include <stdio.h>
#include <stdlib.h>
#include "inputHandler.h"

void addVertex(adjList *list, int v, int weight){
    adjVertex *vertex = (adjVertex*) malloc(sizeof(addVertex));
    vertex->next = list->head;
    vertex->vertex = v;
    vertex->weight = weight;

    list->size++;
    list->head = vertex;
}

adjList **createAdjLists(FILE *file, int vertices, int edges){
    adjList **lists = (adjList**) malloc((vertices+1) * sizeof(adjList));
    int i, u, v, weight;
    for(i = 1; i <= vertices; i++){
        lists[i] = (adjList*) malloc(sizeof(adjList));
        lists[i]->head = NULL;
        lists[i]->size = 0;
    }
    

    for (i = 0; i < edges; i++){
        fscanf(file, "%d%d%d", &u, &v, &weight);
        addVertex(lists[u], v, weight);
        addVertex(lists[v], u, weight);
    }
    return lists;
}


void freeLists(adjList **adjLists, int vertices){
    int i, j;
    for (i = 1; i <= vertices; i++){
        adjVertex * aux = adjLists[i]->head;
        while(adjLists[i]->head){
            adjLists[i]->head = adjLists[i]->head->next;
            free(aux);
            aux = adjLists[i]->head;
        }
        free(adjLists[i]);
    }
    free(adjLists);
}











