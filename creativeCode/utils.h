#include "./huffman.h"

// Definindo o número máximo de caracteres possíveis (ASCII)
#define CHAR_SIZE 256

// Função para calcular as frequências dos caracteres em um arquivo
void calculateFrequencies(const char *inputFileName, int freq[]);

//Função para preencher o array de dados com caracteres únicos do texto
void fillFrequencieArray(char data[], int freq[], int dataSize);

// Função para liberar a memória alocada para a árvore de Huffman
void freeHuffmanTree(HuffmanNode *root);

// Função para comprimir o ficheiro
void compressFile(const char *inputFileName, const char *outputFileName, int **codes, int *lengths);

// Ficheiro para descompressão do ficheiro
void decompressFile(const char *inputFileName, const char *outputFileName, HuffmanNode *root);