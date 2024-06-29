#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Nomes dos arquivos
const char *inputFileName = "input.txt";
const char *outputFileName = "output.txt";
const char *compressedFileName = "compressed.bin";

int main()
{
    // Array para armazenar as frequências dos caracteres
    int freq[CHAR_SIZE];

    // Calcular as frequências dos caracteres no arquivo de entrada
    calculateFrequencies(inputFileName, freq);

    // Preenche o array de dados com caracteres únicos do texto
    char data[CHAR_SIZE];
    int dataSize = 0;

    fillFrequencieArray(data, freq, dataSize);

    //------------------Criar a lista ordenada de elementos------------------//

    HuffmanList *myList;

    initList(myList);

    fillList(freq, myList);

    printList(myList);

    return 0;
}
