#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

typedef struct adjVertex{
    int vertex;
    int weight;
    struct adjVertex *next;
} adjVertex;


typedef struct adjList{
    int size;
    adjVertex *head;
} adjList;

adjList **createAdjLists(FILE *file, int vertices, int edges);

void freeLists(adjList **adjLists, int vertices);

#endif