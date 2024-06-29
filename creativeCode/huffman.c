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

    return (HuffmanNode *)malloc(sizeof(HuffmanNode *));
    ;
}

// Função para inserir na lista de forma ordenada
void insertInOrderList(HuffmanList *list, HuffmanNode *node)
{

    HuffmanNode *aux = list->node;

    if (aux == NULL || aux->frequency > node->frequency)
    {
        node->next = aux->next;
        list->node = node;
        list->size++;
        return;
    }

    while (aux->next && aux->next->frequency <= node->frequency)
    {
        printf("%c - %d\n", aux->character, aux->frequency);
        aux = aux->next;
    }

    node->next = aux->next;
    aux->next = node;

    list->size++;
}

// Função para inserir os dados provienientes da tabela de frequência
void fillList(int freq[], HuffmanList *list)
{

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (freq[i] > 0)
        {
            HuffmanNode *newNode = initNewHuffmanNode();

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
            {
                printf("\nErro ao alocar memória: fillList()!\n");
                break;
            }
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