#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./utils.h"

#define MAX_CHAR 256 // Definindo o número máximo de caracteres possíveis (ASCII)

// Função para calcular as frequências dos caracteres em um arquivo
void calculateFrequencies(const char* inputFileName, int freq[256])
{

    // Inicializar o array de frequências
    for (int i = 0; i < 256; i++)
    {
        freq[i] = 0;
    }

    // Abrir o arquivo de entrada
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile)
    {
        perror("Erro ao abrir o arquivo de entrada");
        return;
    }

    // Ler o conteúdo do arquivo e calcular as frequências
    int c;
    while ((c = fgetc(inputFile)) != EOF)
    {
        freq[(unsigned char)c]++;
    }

    fclose(inputFile);
}

// Função para liberar a memória alocada para a árvore de Huffman
void freeHuffmanTree(HuffmanNode *root)
{
    if (root)
    {
        freeHuffmanTree(getLeft(root));
        freeHuffmanTree(getRight(root));
        free(root);
    }
}
// Função para comprimir o arquivo de entrada usando os códigos de Huffman
void compressFile(const char *inputFileName, const char *outputFileName, int **codes, int *lengths)
{
    FILE* inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Erro ao abrir o arquivo de entrada para compressão");
        return;
    }

    FILE* outputFile = fopen(outputFileName, "wb");
    if (!outputFile) {
        perror("Erro ao abrir o arquivo de saída para compressão");
        fclose(inputFile);
        return;
    }

    unsigned char buffer = 0;
    int bufferLen = 0;
    int c;

    while ((c = fgetc(inputFile)) != EOF) {
        int* code = codes[(unsigned char)c];
        int codeLen = lengths[(unsigned char)c];

        for (int i = 0; i < codeLen; i++) {
            buffer = (buffer << 1) | code[i];
            bufferLen++;

            if (bufferLen == 8) {
                fputc(buffer, outputFile);
                buffer = 0;
                bufferLen = 0;
            }
        }
    }

    // Escrever os bits restantes e o número de bits válidos na última byte
    if (bufferLen > 0) {
        buffer = buffer << (8 - bufferLen); // Alinhar bits restantes à esquerda
        fputc(buffer, outputFile);
        fputc(bufferLen, outputFile); // Armazenar o número de bits válidos
    } else {
        fputc(8, outputFile); // Caso não haja bits restantes, armazenar 8
    }

    fclose(inputFile);
    fclose(outputFile);
}

void decompressFile(const char *inputFileName, const char *outputFileName, HuffmanNode *root)
{
    FILE* inputFile = fopen(inputFileName, "rb");
    if (!inputFile) {
        perror("Erro ao abrir o arquivo de entrada para descompressão");
        return;
    }

    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        perror("Erro ao abrir o arquivo de saída para descompressão");
        fclose(inputFile);
        return;
    }

    HuffmanNode* currentNode = root;
    unsigned char buffer;
    int bufferLen = 8; // Inicialmente, assumimos 8 bits por byte

    // Ler o número de bits válidos na última byte
    fseek(inputFile, -1, SEEK_END);
    int lastByteBits = fgetc(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    while (fread(&buffer, 1, 1, inputFile)) {
        if (ftell(inputFile) == ftell(inputFile) - 1) { // Verifica se é o último byte
            bufferLen = lastByteBits;
        }

        for (int i = 7; i >= (8 - bufferLen); --i) {
            int bit = (buffer >> i) & 1;

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
