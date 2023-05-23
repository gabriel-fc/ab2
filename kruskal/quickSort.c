#include <stdio.h>
#include "quickSort.h"




void swap(edge **edgesList, int a, int b) {
    edge *aux = edgesList[a];
    edgesList[a] = edgesList[b];
    edgesList[b] = aux;
}

int partition(edge **edgesList, int beginning, int length) {
    int pivotIndex = beginning + length -1;
    edge *pivot = edgesList[pivotIndex];
    int i = beginning - 1;

    for (int j = beginning; j <= pivotIndex; j++) {
        if (edgesList[j]->weight <= pivot->weight) {
            i++;
            if(i!=j) swap(edgesList, i, j);
        }
    }
    return i;
}

void sort(edge **edgesList, int beginning, int length) {
    if (length > 1) {
        int pivot = partition(edgesList, beginning, length); 
        sort(edgesList, beginning, pivot-beginning);
        sort(edgesList, pivot + 1, length - pivot - 1);
    }
}
