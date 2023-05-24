#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../prim/heap.h"
#include "../prim/inputHandler.h"



void relax(int u, int v, int weight, qList *q){
    int position = q->elementPosition[v];
    if(weight < q->heap[position]->key){
        // printf("vertex v == %d with current key == %d receiving %d\n", v, q->heap[position]->key, weight);
        decreaseKey(position, weight, u, q);
    }
}



qElement **dijkstra(int vertices, int root, adjList **adjLists){
    qList *q = initHeap(vertices, root);
    qElement **s = (qElement**) malloc(vertices *sizeof(qElement));
    int sSize = 0;

    while(q->size){
        qElement * u = pop(q);
        s[sSize++] = u;
        adjVertex * v = adjLists[u->vertex]->head;
        // printf("u: %d\n", u->vertex);
        while (v){
            int vPosition = q->elementPosition[v->vertex];
            if(vPosition != -1){
                int weight = v->weight;
                // printf("%d\n", v->weight);
                if(u->vertex != root){
                    weight += u->key;
                }
                relax(u->vertex, v->vertex, weight, q);
            }
            
            v = v->next;
        }        
    }
    return s;
}









void main(int argc, char *argv[]){

    int vertices, edges, i, root = 1;
    char *fileName = (char*)malloc(100 * sizeof(char));
    char *execCommand = (char*)malloc(100 * sizeof(char));
    
    for (i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-f")) fileName = argv[++i];
        else if(!strcmp(argv[i], "-i")) root = atoi(argv[++i]);
        else if(!strcmp(argv[i], "-h")) execCommand = argv[i];
    }
    FILE *file = fopen(fileName, "r");
     if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fscanf(file, "%d%d", &vertices, &edges);
    adjList **adjLists = createAdjLists(file, vertices, edges);
    qList *q = initHeap(vertices, root);
    qElement **s = dijkstra(vertices, root, adjLists);
    

    if(!strcmp(execCommand, "-h")){}
    else {
        for (i = 0; i < vertices; i++){
            printf("%d:%d ", s[i]->vertex, s[i]->key < INT_MAX ? s[i]->key : -1);
        }
    };

    freeLists(adjLists, vertices);
}






