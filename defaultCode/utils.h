#include "huffmanTree.h"

// Função para calcular as frequências dos caracteres em um arquivo
void calculateFrequencies(const char* inputFileName, int freq[256]);

// Função para liberar a memória alocada para a árvore de Huffman
void freeHuffmanTree(HuffmanNode *root);

// Função para comprimir o ficheiro
void compressFile(const char *inputFileName, const char *outputFileName, int **codes, int *lengths);

// Ficheiro para descompressão do ficheiro
void decompressFile(const char *inputFileName, const char *outputFileName, HuffmanNode *root);