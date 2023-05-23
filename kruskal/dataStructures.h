#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct edge{
    int u;
    int v;
    int weight;
} edge;


typedef struct vertex{
    int rank;
    int parent;
} vertex;

#endif