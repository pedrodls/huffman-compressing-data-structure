#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    struct huffmanNode *start;

} HuffmanList;

// Função para inicializar a lista
HuffmanList *initList(HuffmanList *list)
{
    list->start = NULL;
    list->size = 0;
}

// Função para inicializar no
HuffmanNode *initNewHuffmanNode()
{

    return (HuffmanNode *)malloc(sizeof(HuffmanNode *));
}

// Função para inserir na lista de forma ordenada
void insertInOrderList(HuffmanList *list, HuffmanNode *newNode)
{

    HuffmanNode *aux = NULL;

    if (list->start == NULL)
    {
        list->start = newNode;
    }
    else if (newNode->frequency < list->start->frequency)
    {
        newNode->next = list->start;
        list->start = newNode;
    }
    else
    {
        aux = list->start;
        while (aux->next && aux->next->frequency <= newNode->frequency)
        {
            aux = aux->next;
        }
        newNode->next = aux->next;
        aux->next = newNode;
    }

    list->size++;
}

// Função para inserir os dados provienientes da tabela de frequência
void fillList(int freq[], HuffmanList *list)
{

    HuffmanNode *newNode;

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (freq[i] > 0)
        {

            newNode = (HuffmanNode *)malloc(sizeof(HuffmanNode));

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
    HuffmanNode *aux = list->start;

    printf("\tLista Ordenada: Tamanho %d\n", list->size);

    while (aux)
    {
        printf("\tCaracter: %c Frequencia: %d\n", aux->character, aux->frequency);
        aux = aux->next;
    }
}

// Função para remover um nó
HuffmanNode *removeFromStart(HuffmanList *list)
{
    HuffmanNode *aux = NULL;

    if (list->start)
    {
        aux = list->start;
        list->start = aux->next;
        aux->next = NULL;
        list->size--;
    }

    return aux;
}

// Função para criar a árvore de huffman
HuffmanNode *buildHuffmanTree(HuffmanList *myList)
{
    HuffmanNode *first, *second, *newNode;

    while (myList->size > 1)
    {
        first = removeFromStart(myList);
        second = removeFromStart(myList);
        newNode = (HuffmanNode *)malloc(sizeof(HuffmanNode));

        if (newNode)
        {
            newNode->character = '+'; /*Opcional esse preenchimento*/
            newNode->frequency = first->frequency + second->frequency;
            newNode->left = first;
            newNode->right = second;
            newNode->next = NULL;

            insertInOrderList(myList, newNode);
        }
        else
        {
            printf("\n\tErro! ao alocar memória: buildHuffmanTree()!\n");
            break;
        }
    }

    return myList->start;
}

// Função para imprimir a árvore
void printHuffmanTree(HuffmanNode *cetralNode, int size)
{
    if (cetralNode->left == NULL && cetralNode->right == NULL)
    {
        printf("\tFolha: %c\t Altura: %d\n", cetralNode->character, size);
    }
    else
    {
        printHuffmanTree(cetralNode->left, size + 1);
        printHuffmanTree(cetralNode->right, size + 1);
    }
}

// Função para calcular a altura da árvore
int heightOfHuffmanTree(HuffmanNode *centralNode)
{

    int right, left;

    if (centralNode == NULL)
        return -1;
    else
    {
        left = heightOfHuffmanTree(centralNode->left) + 1;
        right = heightOfHuffmanTree(centralNode->right) + 1;

        if (left > right)
            return left;

        return right;
    }
}

// Função para alocar de forma dinâmica o dicionário(Tabela)
char **allocateDictionary(int columns)
{

    char **dictionary = malloc(sizeof(char *) * CHAR_SIZE);

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        dictionary[i] = calloc(columns, sizeof(char));
    }

    return dictionary;
}

// Função para gerar dicionário
void generateDictionary(char **dictionary, HuffmanNode *centralNode, char *way, int columns)
{
    char left[columns], right[columns];

    if (centralNode->left == NULL && centralNode->right == NULL)
    {
        strcpy(dictionary[centralNode->character], way);
    }
    else
    {
        strcpy(left, way);
        strcpy(right, way);

        strcat(left, "0");
        strcat(right, "1");

        generateDictionary(dictionary, centralNode->left, left, columns);
        generateDictionary(dictionary, centralNode->right, right, columns);
    }
}

// Função para imprimir o dicionário
void printDictionary(char **dictionary)
{

    printf("\t\nDicionário:\n");

    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (strlen(dictionary[i]) > 0)
            printf("\t%3d: %s\n", i, dictionary[i]);
    }
}

// Função para calcular o tamanho da String
int calculateStringSize(char **dictionary, unsigned char *text)
{
    int i = 0, size = 0;
    while (text[i] != '\0')
    {
        size = size + strlen(dictionary[text[i]]);
        i++;
    }

    return size + 1;
}

// Função para codificar a string
char *encodeString(char **dictionary, unsigned char *text)
{

    int i = 0, size = calculateStringSize(dictionary, text);

    char *code = (char *)calloc(size, sizeof(char));

    while (text[i] != '\0')
    {
        strcat(code, dictionary[text[i]]);
        i++;
    }

    return code;
}

// Função para decodificar a string
char *decodedString(unsigned char text[], HuffmanNode *centralNode)
{

    HuffmanNode *aux = centralNode;

    int i = 0;
    char temp[2];
    char *decodedData = (char *)calloc(strlen(text), sizeof(char));

    while (text[i] != '\0')
    {
        if (text[i] == '0')
        {
            aux = aux->left;
        }
        else
        {
            aux = aux->right;
        }

        if (aux->left == NULL && aux->right == NULL)
        {
            temp[0] = aux->character;
            temp[1] = '\0';
            strcat(decodedData, temp);
            aux = centralNode;
        }

        i++;
    }

    return decodedData;
}

// Função para compactar
void compact(unsigned char str[])
{

    FILE *file = fopen("compactado.wg", "wb");

    int i = 0, j = 7;

    unsigned char mascara, byte = 0;

    if (file)
    {
        while (str[i] != '\0')
        {
            mascara = 1;
            if (str[i] == '1')
            {
                mascara = mascara << j;
                byte = byte | mascara;
            }
            j--;

            if (j < 0)
            { // Tem um byte formado
                fwrite(&byte, sizeof(unsigned char), 1, file);
                byte = 0;
                j = 7;
            }
            i++;
        }

        if (j != 7)
        {
            fwrite(&byte, sizeof(unsigned char), 1, file);
        }

        printf("\nArquivo compactado\n");

        fclose(file);
    }
    else
    {
        printf("\nErro ao Abrir/Criar file em compactar\n");
    }
}

// Função para verificar bit
unsigned int verifyBit(unsigned char byte, int i)
{
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

// Função para descompactar
void decompact(HuffmanNode *centralNode)
{

    FILE *file = fopen("compactado.wg", "rb");

    HuffmanNode *aux = centralNode;

    unsigned char byte;

    int i;

    if (file)
    {
        while (fread(&byte, sizeof(unsigned char), 1, file))
        {
            for (i = 7; i >= 0; i--)
            {
                if (verifyBit(byte, i))
                {
                    aux = aux->right;
                }
                else
                {
                    aux = aux->left;
                }
                if (aux->left == NULL && aux->right == NULL)
                {
                    printf("%c", aux->character);
                    aux = centralNode;
                }
            }
        }
        fclose(file);
    }
    else
    {
        printf("\nErro ao Abrir file em descompactar\n");
    }
}