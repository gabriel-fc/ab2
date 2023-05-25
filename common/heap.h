#ifndef HEAP_H
#define HEAP_H
typedef struct qElement{
    int vertex;
    int neighbor;
    int key;
} qElement;


typedef struct qList{
    qElement **heap;
    int size;
    int *elementPosition;
}qList;

int isInf(int value);

qList *initHeap(int vertices, int root);

void decreaseKey(int i, int key, int neighbor, qList *q);

void printElementIndices(qList *q, int vertices);

void printQ(qList *q);

qElement *pop(qList *q);

void freeQ(qList *q);
#endif