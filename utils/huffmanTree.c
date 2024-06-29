#include <stdio.h>
#include <stdlib.h>
#include "./minHeap.h"

#define SIZE_CHAR 256
// Estrutura do nó da árvore de Huffman
typedef struct huffmanNode
{
    char character;
    int frequency;
    struct huffmanNode *left;
    struct huffmanNode *right;

}HuffmanNode;

// Função para criar um novo nó de Huffman
HuffmanNode *createNode(char character, int frequency)
{
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//Função para pegar a frequência
int getFrequency(HuffmanNode *node){
    return node->frequency;
}

//Função para pegar a frequência
HuffmanNode* getLeft(HuffmanNode *node){
    return node->left;
}

//Função para pegar a frequência
HuffmanNode* getRight(HuffmanNode *node){
    return node->right;
}

// Função para pegar o caracter
char getCharacter(HuffmanNode *node){
    return node->character;
}

// Função para construir a árvore de Huffman
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    HuffmanNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Função para verificar se um nó é uma folha
int isLeaf(HuffmanNode* root) {
    return !(root->left) && !(root->right);
}

// Função para armazenar os códigos de Huffman em um array
void storeCodes(HuffmanNode* root, int arr[], int top, int** codes, int* lengths) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes, lengths);
    }

    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes, lengths);
    }

    if (isLeaf(root)) {
        codes[root->character] = (int*)malloc(top * sizeof(int));
        lengths[root->character] = top;
        for (int i = 0; i < top; ++i)
            codes[root->character][i] = arr[i];
    }
}

//Função para imprimir os códigos dos caracteres
void printCodes(HuffmanNode* root, int* arr, int top) {
    // Adiciona 0 para o filho esquerdo e recursivamente chama a função
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Adiciona 1 para o filho direito e recursivamente chama a função
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // Se o nó atual é uma folha, então é um dos caracteres a ser codificado
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Função principal para construir a árvore de Huffman e gerar os códigos
void HuffmanCodes(char data[], int freq[], int size, int** codes, int* lengths) {
    HuffmanNode* root = buildHuffmanTree(data, freq, size);
    int arr[SIZE_CHAR], top = 0;
    storeCodes(root, arr, top, codes, lengths);
}