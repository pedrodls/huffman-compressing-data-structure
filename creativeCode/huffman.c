#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 256

// Estrutura do nó da árvore de Huffman
typedef struct huffmanNode
{
    char character;
    int frequency;
    struct huffmanNode *left;
    struct huffmanNode *right;
    struct huffmanNode *next;

} HuffmanNode;

// Estrutura da lista
typedef struct huffmanList
{
    int size;
    struct huffmanNode *node;

} HuffmanList;

// Função para inicializar a lista
HuffmanList *initList(HuffmanList *list)
{
    list->node = NULL;
    list->size = 0;
}

// Função para inicializar no
HuffmanNode *initNewHuffmanNode()
{
    return malloc(sizeof(HuffmanNode));
}

// Função para inserir na lista de forma ordenada
void insertInOrderList(HuffmanList *list, HuffmanNode *node)
{

    HuffmanNode *aux;

    if (!list->node)
    {
        list->node = node;
    }
    else if (list->node->frequency > node->frequency)
    {
        node->next = list->node;
        list->node = node;
    }
    else
    {
        aux = list->node;

        while (aux->next && aux->next->frequency <= node->frequency)
            aux = aux->next;

        node->next = aux->next;
        aux->next = node;
    }

    list->size++;
}

// Função para inserir os dados provienientes da tabela de frequência
void fillList(unsigned int freq[], HuffmanList *list)
{

    HuffmanNode *newNode;

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (freq[i] > 0)
        {
            newNode = initNewHuffmanNode();

            if (newNode)
            {
                newNode->character = i;
                newNode->frequency = freq[i];
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->next = NULL;

                insertInOrderList(list, newNode);
            }
            else
                printf("\nErro ao alocar memória: fillList()!\n");
            break;
        }
    }
}

// Função para imprimir a lista
void printList(HuffmanList *list)
{
    HuffmanNode *aux = list->node;

    printf("\tLista Ordenada: Tamanho %d\n", list->size);

    while (aux)
    {
        printf("\tCaracter: %c Frequencia: %d\n", aux->character, aux->frequency);
        aux = aux->next;
    }
}