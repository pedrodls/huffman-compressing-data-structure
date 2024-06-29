#include "./huffmanTree.h"

typedef struct minHeap MinHeap;


// Função para construir a min-heap
void buildMinHeap(MinHeap* minHeap) ;

// Função para criar uma min-heap com capacidade específica
MinHeap *createMinHeap(unsigned capacity);

// Função para criar e construir uma min-heap a partir de um array de caracteres e frequências
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);

// Função para trocar dois nós no heap
void swapNodes(HuffmanNode **a, HuffmanNode **b);

// Função para garantir que a propriedade de min-heap seja mantida
void minHeapify(MinHeap *minHeap, int idx);

// Função para inserir um nó na min-heap
void insertMinHeap(MinHeap *minHeap, HuffmanNode *minHeapNode);

// Função para extrair o nó com menor frequência da min-heap
HuffmanNode *extractMin(MinHeap *minHeap);

// Função para verificar se o tamanho da min-heap é um
int isSizeOne(MinHeap *minHeap);