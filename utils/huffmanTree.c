
#include <stdlib.h>
#include "./minHeap.h"

// Estrutura do nó da árvore de Huffman
typedef struct huffmanNode
{
    char character;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;

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

// Função para construir a árvore de Huffman
HuffmanNode* buildHuffmanTree(char* data, int* freq, int size) {
    HuffmanNode *left, *right, *top;

    // Cria uma fila de prioridade (heap mínimo) com capacidade igual ao número de caracteres únicos
    MinHeap* minHeap = createMinHeap(size);

    // Insere todos os caracteres no heap mínimo
    for (int i = 0; i < size; ++i)
        insertMinHeap(minHeap, createNode(data[i], freq[i]));

    // Itera enquanto o tamanho do heap não for igual a 1
    while (getSize(minHeap) != 1) {
        // Extrai os dois nós de menor frequência do heap mínimo
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Cria um novo nó com a soma das frequências dos dois nós extraídos
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // Insere o novo nó no heap mínimo
        insertMinHeap(minHeap, top);
    }

    // O nó restante no heap é a raiz da árvore de Huffman
    return extractMin(minHeap);
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

//Função para pegar os códigos binários
void HuffmanCodes(char* data, int* freq, int size) {
    // Constroi a árvore de Huffman
    HuffmanNode* root = buildHuffmanTree(data, freq, size);

    // Array para armazenar os códigos de Huffman
    int arr[100], top = 0;

    // Gera e imprime os códigos de Huffman
    printCodes(root, arr, top);
}
