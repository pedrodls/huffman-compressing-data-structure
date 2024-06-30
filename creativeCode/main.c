#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <windows.h> // Para SetConsoleOutput

// Nomes dos arquivos
const char *inputFileName = "./input.txt";



void toCompact() {

}

int main()
{

    /*--------------------- PARTE 1: TABELA DE FREQUêNCIA ----------------------*/

    int freq[CHAR_SIZE];
    int fileSize = getFileSize();
    unsigned char *data = calloc(fileSize * 2, sizeof(unsigned char));

    // Preenche o array de dados com caracteres únicos do texto
    readFileText(data);

    initFrequencyTab(freq);
    fillFrequencyTab(data, freq);

    //printTabFrequency(freq);

    /*--------------------- PARTE 2: LISTA ENCADEADA ORDENADA -------------------*/

    HuffmanList *myList = (HuffmanList *)malloc(sizeof(HuffmanList *));

    initList(myList);

    fillList(freq, myList);

    //printList(myList);

    /*--------------------- PARTE 3: Montar árvore de  Huffman -----------------*/

    HuffmanNode *huffmanTree = buildHuffmanTree(myList);
    //printf("Arvore de Ruffman\n");
    //printHuffmanTree(huffmanTree, 0);


    /*--------------------- PARTE 4: Montar o Dicionário ------------------------*/
    int columns = heightOfHuffmanTree(huffmanTree) + 1;
    char **dictionary = allocateDictionary(columns);

    generateDictionary(dictionary, huffmanTree, "", columns);
    //printDictionary(dictionary);


    /*--------------------- PARTE 5: Codificando ------------------------*/
    char *encodedData = encodeString(dictionary, data);
    printf("\n\tTexto codificado: %s\n", encodedData);


    /*--------------------- PARTE 6: Decodificar ----------------------------------*/
    char *decodedData = decodedString(encodedData, huffmanTree);
    printf("\n\tTexto descodificado: %s\n", decodedData);

    /*--------------------- PARTE 7: Compactar----------------------------------*/
    compact(encodedData);

    /*--------------------- PARTE 8: Descompactar----------------------------------*/

    decompact(huffmanTree);
    printf("\n\n");

    free(encodedData);
    free(decodedData);

    return 0;
}
