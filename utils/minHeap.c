#include <stdlib.h>
#include "./minHeap.h"
#include "minHeap.h"

struct minHeap {
    int size;
    int capacity;
    HuffmanNode** array;
};

// Função para criar uma nova fila de prioridade (heap mínimo)
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode**)malloc(minHeap->capacity * sizeof(HuffmanNode*));
    return minHeap;
}

// Função para trocar dois nós no heap
void swapNodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* t = *a;
    *a = *b;
    *b = t;
}

// Função para fazer heapify no heap mínimo
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && getFrequency(minHeap->array[left]) < getFrequency(minHeap->array[smallest]))
        smallest = left;

    if (right < minHeap->size && getFrequency(minHeap->array[right]) < getFrequency(minHeap->array[smallest]))
        smallest = right;

    if (smallest != idx) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Função para inserir um nó no heap mínimo
void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    minHeap->size++;
    int i = minHeap->size - 1;
    while (i && getFrequency(node) < getFrequency(minHeap->array[(i - 1) / 2])) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// Função para extrair o nó de menor frequência do heap mínimo
HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}


//Função para pegar o size
int getSize(MinHeap *minHeap)
{
    return minHeap->size;
}