#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./utils.h"

#define MAX_CHAR 256 // Definindo o número máximo de caracteres possíveis (ASCII)

// Função para liberar a memória alocada para a árvore de Huffman
void freeHuffmanTree(HuffmanNode* root) {
    if (root) {
        freeHuffmanTree(getLeft(root));
        freeHuffmanTree(getRight(root));
        free(root);
    }
}
// Função para comprimir o arquivo de entrada usando os códigos de Huffman
void compressFile(const char* inputFileName, const char* outputFileName, int** codes, int* lengths) {
    FILE* inputFile = fopen(inputFileName, "r");
    FILE* outputFile = fopen(outputFileName, "wb");

    if (!inputFile || !outputFile) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    unsigned char buffer = 0;
    int bufferLength = 0;

    int c;
    while ((c = fgetc(inputFile)) != EOF) {
        for (int i = 0; i < lengths[c]; ++i) {
            buffer = (buffer << 1) | codes[c][i];
            bufferLength++;

            if (bufferLength == 8) {
                fwrite(&buffer, 1, 1, outputFile);
                buffer = 0;
                bufferLength = 0;
            }
        }
    }

    if (bufferLength > 0) {
        buffer = buffer << (8 - bufferLength);
        fwrite(&buffer, 1, 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}

// Função para descomprimir o arquivo comprimido usando a árvore de Huffman
void decompressFile(const char* inputFileName, const char* outputFileName, HuffmanNode* root) {
    FILE* inputFile = fopen(inputFileName, "rb");
    FILE* outputFile = fopen(outputFileName, "w");

    if (!inputFile || !outputFile) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    HuffmanNode* currentNode = root;
    int bit;
    unsigned char buffer;
    while (fread(&buffer, 1, 1, inputFile)) {
        for (int i = 7; i >= 0; --i) {
            bit = (buffer >> i) & 1;

            if (bit == 0)
                currentNode = getLeft(currentNode);
            else
                currentNode = getRight(currentNode);

            if (isLeaf(currentNode)) {
                fputc(getCharacter(currentNode), outputFile);
                currentNode = root;
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}
