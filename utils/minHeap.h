#include "./huffmanTree.h"

typedef struct minHeap MinHeap;

// Função para criar uma nova fila de prioridade (heap mínimo)
MinHeap *createMinHeap(int capacity);

// Função para trocar dois nós no heap
void swapNodes(HuffmanNode **a, HuffmanNode **b);

// Função para fazer heapify no heap mínimo
void minHeapify(MinHeap *minHeap, int idx);

// Função para inserir um nó no heap mínimo
void insertMinHeap(MinHeap *minHeap, HuffmanNode *node);

// Função para extrair o nó de menor frequência do heap mínimo
HuffmanNode *extractMin(MinHeap *minHeap);

// Função para pegar o size
int getSize(MinHeap *minHeap);