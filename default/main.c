#include <stdio.h>
#include <stdlib.h>
#include "./minHeap.h"
#include "./utils.h"
#include <windows.h> // Para SetConsoleOutput

int main()
{

    /* char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]); */

    SetConsoleOutputCP(65001);

    /*
    Para Alterar a formatação de strData do prompt de comando(CMD)
    para aceitar a acentuaÇÃO.
    */

    unsigned char *strData, *arr;
    unsigned int freqTable[TAM];
    int tam, count = 0;

    tam = findSize();
    // printf("\nQuantidade: %d\n", tam);

    strData = calloc(tam * 2, sizeof(unsigned char));

    readText(strData);

    /*--------------------- PARTE 1: TABELA DE FREQUNCIA----------------------*/

    initTable(freqTable);
    fillFreqTable(strData, freqTable);
    // printFreqTable(freqTable);

    arr = calloc(tam * 2, sizeof(unsigned char));

    for (int i = 0; i < TAM; i++)
    {
        if (freqTable[i] > 0)
        {
            arr[count] = i;

            count++;
        }
        else
        {
            arr[count] = '\0';
        }
    }

    /*--------------------- PARTE 2: ÁRVORE DE HUFFMAN----------------------*/

    HuffmanCode *codes = (HuffmanCode *)malloc(tam * sizeof(HuffmanCode *));

    HuffmanCodes(arr, freqTable, strlen(arr), codes);

    const char *inputFilename = "input.txt";
    const char *compressedFilename = "./compressed/compressed.txt";
    const char *decompressedFilename = "./compressed/decompressed.txt";

    compressFile(inputFilename, compressedFilename, codes, strlen(arr));
    printf("Arquivo comprimido com sucesso!\n");

    free(codes);
    free(arr);
    free(strData);

    decompressFile(compressedFilename, decompressedFilename);
    printf("Arquivo descomprimido com sucesso!\n");

    return 0;
}
