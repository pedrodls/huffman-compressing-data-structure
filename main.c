#include <stdio.h>
#include <stdlib.h>
#include "./utils/minHeap.h"
#include "./utils/utils.h"

int main()
{

    // Nome do arquivo de entrada
    const char *inputFileName = "./utils/input.txt";
    const char *outputFileName = "./utils/output.txt";
    const char *compressedFileName = "./utils/compressed.bin";

    // Array para armazenar as frequências dos caracteres
    int freq[256];

    // Calcular as frequências dos caracteres no arquivo de entrada
    calculateFrequencies(inputFileName, freq);

    // Preenche o array de dados com caracteres únicos do texto
    char data[256];
    int dataSize = 0;
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            data[dataSize] = i;
            dataSize++;
        }
    }

    // Alocação de memória para armazenar os códigos e seus comprimentos
    int **codes = (int **)calloc(256, sizeof(int *));
    int *lengths = (int *)calloc(256, sizeof(int));

    // Gerar os códigos de Huffman
    printf("Gerando os códigos de Huffman...\n");
    HuffmanCodes(data, freq, dataSize, codes, lengths);

    // Compressão do arquivo de entrada
    printf("Compressão do arquivo de entrada...\n");
    compressFile(inputFileName, compressedFileName, codes, lengths);

    // Construir a árvore de Huffman a partir dos dados e frequências
    printf("Construindo a árvore de Huffman...\n");
    HuffmanNode *root = buildHuffmanTree(data, freq, dataSize);

    // Descompressão do arquivo comprimido
    printf("Descompressão do arquivo comprimido...\n");
    decompressFile(compressedFileName, outputFileName, root);

    // Liberação de memória alocada para códigos
    printf("Liberando memória alocada para códigos...\n");

    for (int i = 0; i < 256; i++)
    {
        if (codes[i])
            free(codes[i]);
    }

    free(codes);
    free(lengths);

    // Libera a árvore de Huffman
    printf("Liberando memória da árvore de Huffman...\n");
    freeHuffmanTree(root);

    printf("Processo concluído.\n");

    return 0;
}
