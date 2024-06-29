#include <stdio.h>
#include <stdlib.h>
#include "./utils/minHeap.h"
#include "./utils/utils.h"

int main()
{
    // Exemplo de texto para compressão
    char text[] = "exemplo de texto para compressão e descompressão usando Huffman";
    int freq[256] = {0};

    // Calcula a frequência de cada caractere no texto
    for (int i = 0; text[i]; i++)
        freq[(unsigned char)text[i]]++;

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
    HuffmanCodes(data, freq, dataSize, codes, lengths);

    // Compressão do arquivo de entrada
    compressFile("./utils/input.txt", "./utils/compressed.bin", codes, lengths);

    // Construir a árvore de Huffman a partir dos dados e frequências
    HuffmanNode *root = buildHuffmanTree(data, freq, dataSize);

    // Descompressão do arquivo comprimido
    decompressFile("./utils/compressed.bin", "./utils/output.txt", root);

    // Liberação de memória alocada para códigos
    for (int i = 0; i < 256; i++)
    {
        if (codes[i])
            free(codes[i]);
    }
    free(codes);
    free(lengths);

    // Libera a árvore de Huffman
    freeHuffmanTree(root);

    printf("Done!");

    return 0;
}
