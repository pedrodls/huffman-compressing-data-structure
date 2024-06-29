#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./utils.h"

#define MAX_CHAR 256 // Definindo o número máximo de caracteres possíveis (ASCII)

/* void getFrequency(char *str, int freq[])
{
    // Inicializando o array de frequências com 0
    for (int i = 0; i < MAX_CHAR; i++)
        freq[i] = 0;

    // Percorrendo a string e contando a frequência de cada caractere
    for (int i = 0; str[i] != '\0'; i++)
        freq[(unsigned char)str[i]]++;
        
} */

//Função para comprimir o ficheiro
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

//Ficheiro para descompressão do ficheiro
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
