#include <stdio.h>
#include <stdlib.h>
#include "./utils/minHeap.h"
#include "./utils/utils.h"

int main() {
    char text[] = "exemplo de texto para compressão e descompressão usando Huffman";
    int freq[256] = {0};

    for (int i = 0; text[i]; i++)
        freq[(unsigned char)text[i]]++;

    char data[256];
    int dataSize = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[dataSize] = i;
            dataSize++;
        }
    }

    int** codes = (int**)malloc(256 * sizeof(int*));
    int* lengths = (int*)malloc(256 * sizeof(int));

    HuffmanCodes(data, freq, dataSize, codes, lengths);

    compressFile("input.txt", "compressed.bin", codes, lengths);

    HuffmanNode* root = buildHuffmanTree(data, freq, dataSize);

    decompressFile("compressed.bin", "output.txt", root);

    // Liberar memória alocada
    for (int i = 0; i < 256; i++) {
        if (codes[i])
            free(codes[i]);
    }
    
    free(codes);
    free(lengths);

    return 0;
}
