#include <stdio.h>
#include <stdlib.h>
#include "Comprimir_Descomprimir.h"
#include <windows.h> // Para SetConsoleOutput
#define TAM 256

int main()
{

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

void encodeFromMain()
{

    unsigned char *strData;
    unsigned int freqTable[TAM];
    list myList;
    node *huffmanTree;
    int columns, tam;
    char **dictionary;
    char *codificado, *descodificado;

    /*Para Alterar a formatação de strData do prompt de comando(CMD)
    para aceitar a acentua��o.
    */

    tam = findSize();
    // printf("\nQuantidade: %d\n", tam);

    strData = calloc(tam * 2, sizeof(unsigned char));
    readText(strData);
    // printf("\nTEXTO:\n%s\n", strData);

    /*--------------------- PARTE 1: TABELA DE FREQUNCIA----------------------*/

    initTable(freqTable);
    fillFreqTable(strData, freqTable);
    // printFreqTable(freqTable);

    /*--------------------- PARTE 2: myListA ENCADEADA ORDENADA-------------------*/

    createList(&myList);
    fillList(freqTable, &myList);
    // printList(&myList);

    /*--------------------- PARTE 3: Montar árvore de  Huffman -----------------*/
    huffmanTree = mountHuffmanTree(&myList);
    // printf("Árvore de Ruffman\n");
    //  printHuffmanTree(huffmanTree, 0);

    /*--------------------- PARTE 4: Montar o Dicionário ------------------------*/
    columns = huffmanTreeHeight(huffmanTree) + 1;
    dictionary = allocateDictionary(columns);
    generateDictionary(dictionary, huffmanTree, "", columns);
    // printDictionary(dictionary);

    /*--------------------- PARTE 5: Codificar ----------------------------------*/
    codificado = encode(dictionary, strData);
    printf("\n\tTexto codificado: %s\n", codificado);

    /*--------------------- PARTE 6: Decodificar ----------------------------------*/
    descodificado = decode(codificado, huffmanTree);
    printf("\n\tTexto original: %s\n", descodificado);

    /*--------------------- PARTE 7: Compactar----------------------------------*/

    saveTable(freqTable);

    compact(codificado);

    free(strData);
    free(codificado);
    free(descodificado);
}

void decodeFromMain()
{

    /*--------------------- PARTE 1: TABELA DE FREQUNCIA----------------------*/

    unsigned int freqTable[TAM];
    list myList;
    node *huffmanTree;

    initTable(freqTable);

    readTable(freqTable);

    /*--------------------- PARTE 2: myListA ENCADEADA ORDENADA-------------------*/

    createList(&myList);
    fillList(freqTable, &myList);

    /*--------------------- PARTE 3: Montar árvore de  Huffman -----------------*/
    huffmanTree = mountHuffmanTree(&myList);

    uncompact(huffmanTree);
}
