#include <stdio.h>
#include <stdlib.h>
#include "Comprimir_Descomprimir.h"
#include <windows.h> // Para SetConsoleOutput
#define TAM 256

int main()
{
    void encodeFromMain();

    SetConsoleOutputCP(65001);

    encodeFromMain();

    return 0;
}

void encodeFromMain()
{

    unsigned char *strData;
    unsigned int tabela_frequencia[TAM];
    list myList;
    node *huffmanTree;
    int columns, tam;
    char **dictionary;
    char *codificado, *descodificado;

    /*Para Alterar a formatação de strData do prompt de comando(CMD)
    para aceitar a acentua��o.
    */

    tam = findSize();
    printf("\nQuantidade: %d\n", tam);

    strData = calloc(tam * 2, sizeof(unsigned char));
    readText(strData);
    // printf("\nTEXTO:\n%s\n", strData);

    /*--------------------- PARTE 1: TABELA DE FREQUNCIA----------------------*/

    initTable(tabela_frequencia);
    fillFreqTable(strData, tabela_frequencia);
    // printFreqTable(tabela_frequencia);

    /*--------------------- PARTE 2: myListA ENCADEADA ORDENADA-------------------*/

    createList(&myList);
    fillList(tabela_frequencia, &myList);
    // printList(&myList);

    /*--------------------- PARTE 3: Montar árvore de  Huffman -----------------*/
    huffmanTree = mountHuffmanTree(&myList);
    printf("Árvore de Ruffman\n");
    //printHuffmanTree(huffmanTree, 0);

    /*--------------------- PARTE 4: Montar o Dicionário ------------------------*/
    columns = huffmanTreeHeight(huffmanTree) + 1;
    dictionary = allocateDictionary(columns);
    generateDictionary(dictionary, huffmanTree, "", columns);
    //printDictionary(dictionary);

    /*--------------------- PARTE 5: Codificar ----------------------------------*/
    codificado = encode(dictionary, strData);
    printf("\n\tTexto codificado: %s\n", codificado);

    /*--------------------- PARTE 6: Decodificar ----------------------------------*/
    descodificado = decode(codificado, huffmanTree);
    printf("\n\tTexto descodificado: %s\n", descodificado);

    /*--------------------- PARTE 7: Compactar----------------------------------*/
    compact(codificado);

    /*--------------------- PARTE 8: Descompactar----------------------------------*/
    printf("\nARQUIVO DESCOMPACTADO!\n");
    uncompact(huffmanTree);
    printf("\n\n");

    free(strData);
    free(codificado);
    free(descodificado);
}
