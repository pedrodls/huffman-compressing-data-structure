#include <stdio.h>
#include <stdlib.h>
#include "./utils/minHeap.h"

int main() {

    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };

    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Generating Huffman Codes...\n");
    
    HuffmanCodes(arr, freq, size);

    printf("Finished.\n");

    return 0;
}