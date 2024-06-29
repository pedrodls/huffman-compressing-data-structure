#include "huffmanTree.h"

/* void getFrequency(char *str, int freq[]); */

//Função para comprimir o ficheiro
void compressFile(const char* inputFileName, const char* outputFileName, int** codes, int* lengths);

//Ficheiro para descompressão do ficheiro
void decompressFile(const char* inputFileName, const char* outputFileName, HuffmanNode* root);