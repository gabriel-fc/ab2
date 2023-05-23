#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"


void printElementIndices(qList *q,int vertices){
    int i;
    printf("Indices: ");
    for (i = 1; i <= vertices; i++){
        printf("(v:%d, i:%d) ", i, q->elementPosition[i]);
    }
    printf("\n");
}

void printQ(qList *q){
    int i;
    printf("Q: ");
    for (i = 0; i < q->size; i++){
        printf("(i:%d, v:%d, k:%d) ", i, q->heap[i]->vertex, q->heap[i]->key);
    }
    printf("\n");
}



void swap(int a, int b, qList *q){
    q->elementPosition[q->heap[a]->vertex] = b;
    q->elementPosition[q->heap[b]->vertex] = a;

    qElement *aux = q->heap[a];
    q->heap[a] = q->heap[b];
    q->heap[b] = aux;
}


qElement *createElement(int vertex, int neighbor, int key){
    qElement * el = (qElement*) malloc(sizeof(qElement));
    el->vertex = vertex;
    el->neighbor = neighbor;
    el->key = key;
    return el;
}


qList *initHeap(int vertices, int root){
    qList *q = (qList*) malloc(sizeof(qList));
    q->elementPosition = (int*) malloc((vertices+1) * sizeof(int));
    q->size = vertices;
    q->heap = (qElement**) malloc(vertices * sizeof(qElement));
    int vertex, i = 0;
    //insert root
    q->heap[i++] = createElement(root, 0, 0);
    q->elementPosition[root] = 0;

    //insert V-root vertices
    for(vertex = 1; vertex <= vertices; vertex++){
        if(vertex != root) {
            q->heap[i] = createElement(vertex, 0, INT_MAX);
            q->elementPosition[vertex] = i++;
        }
    }

    return q;
}

void heapify(int i, qList *q) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < q->size && q->heap[left]->key < q->heap[smallest]->key)
        smallest = left;

    if (right < q->size && q->heap[right]->key < q->heap[smallest]->key)
        smallest = right;

    if (smallest != i) {
        swap(i, smallest, q);
        heapify(smallest, q);
    }
}

void decreaseKey(int i, int key, int neighbor, qList *q){
    q->heap[i]->key = key;
    q->heap[i]->neighbor = neighbor;
    int parent = (i - 1)/2;
    while(i > 0){
        if(q->heap[parent]->key > q->heap[i]->key){
            swap(i, parent, q);
            i = parent;
            parent = (i -1)/2;
        }
        else break;
    }
}

qElement *pop(qList *q) {
    if (!q->size){
        printf("popping empty heap!!!\n");
        return NULL;
    }

    qElement *root = q->heap[0];
    q->heap[0] = q->heap[--q->size];
    q->elementPosition[root->vertex] = -1;
    q->elementPosition[q->heap[0]->vertex] = 0;
    heapify(0, q);
    return root;
}

void freeQ(qList *q){
    int i;
    for(i; i < q->size; i++){
        free(q->heap[i]);
    }
    free(q->heap);
    free(q->elementPosition);
    free(q);
}




