#include <stdio.h>
#include <stdlib.h>
#include "./minHeap.h"
#include "./utils.h"
#include <windows.h> // Para SetConsoleOutput

const char *inputFilename = "input.txt";
const char *compressedFilename = "./compressed/compressed.txt";
const char *decompressedFilename = "./compressed/decompressed.txt";

int main()
{
    /*
        Para Alterar a formatação de strData do prompt de comando(CMD)
        para aceitar a acentuaÇÃO.
        */
    void menu();

    SetConsoleOutputCP(65001);

    menu();

    return 0;
}

void menu()
{
    void encodeFromMain();

    void decodeFromMain();

    fflush(stdin);
    system("cls");

    char op;

    printf("\n*******Compact | Descompact******\n");
    printf("* Escolha a sua opcao\t\t*\n");
    printf("* 1 - Compactar\t\t\t*\n");
    printf("* 2 - Descompactar\t\t*\n");
    printf("* 3 - Sair\t\t\t*");
    printf("\n*********************************\n");
    fflush(stdin);

    scanf("%c", &op);

    switch (op)
    {
    case '1':
        encodeFromMain();
        system("pause");
        menu();

    case '2':
        decodeFromMain();
        system("pause");
        menu();

    case '3':
        printf("Volte sempre!");
        exit(0);
        break;
    default:
        printf("\n\nOpcao invalida!\n\n");
        system("pause");
        menu();
    }
}

// Função que gera a compressão
void encodeFromMain()
{

    unsigned char *strData, *arr;
    unsigned int freqTable[TAM];
    int tam, count = 0;

    tam = findSize();

    strData = calloc(tam * 2, sizeof(unsigned char));

    readText(strData);

    /*--------------------- PARTE 1: TABELA DE FREQUÈNCIA----------------------*/

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

    compressFile(inputFilename, compressedFilename, codes, strlen(arr));
    printf("Arquivo comprimido com sucesso, ./compressed/compressed.txt!\n");

    free(codes);
    free(arr);
    free(strData);
}

// Função que gera a descompressão
void decodeFromMain()
{
    decompressFile(compressedFilename, decompressedFilename);
    printf("Arquivo descomprimido com sucesso, encontra-se em ./compressed/decompressed.txt!\n");
}
