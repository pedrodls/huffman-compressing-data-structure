#include <stdlib.h>
#include "./minHeap.h"
#include "minHeap.h"

struct minHeap
{
    int size;
    int capacity;
    HuffmanNode **array;
};

// Função para construir a min-heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Função para criar uma min-heap com capacidade específica
MinHeap *createMinHeap(unsigned capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode **)malloc(minHeap->capacity * sizeof(HuffmanNode *));
    return minHeap;
}

// Função para criar e construir uma min-heap a partir de um array de caracteres e frequências
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Função para trocar dois nós no heap
void swapNodes(HuffmanNode **a, HuffmanNode **b)
{
    HuffmanNode *t = *a;
    *a = *b;
    *b = t;
}

// Função para garantir que a propriedade de min-heap seja mantida
void minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && getFrequency(minHeap->array[left]) < getFrequency(minHeap->array[smallest]))
        smallest = left;

    if (right < minHeap->size && getFrequency(minHeap->array[right]) < getFrequency(minHeap->array[smallest]))
        smallest = right;

    if (smallest != idx)
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Função para inserir um nó na min-heap
void insertMinHeap(MinHeap *minHeap, HuffmanNode *minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && getFrequency(minHeapNode) < getFrequency(minHeap->array[(i - 1) / 2]))
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Função para extrair o nó com menor frequência da min-heap
HuffmanNode *extractMin(MinHeap *minHeap)
{
    HuffmanNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Função para verificar se o tamanho da min-heap é um
int isSizeOne(MinHeap *minHeap)
{
    return (minHeap->size == 1);
}