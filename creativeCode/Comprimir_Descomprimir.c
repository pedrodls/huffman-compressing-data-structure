#include "Comprimir_Descomprimir.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 256

/*---------------------------------PARTE 1: TABELA DE FREQU�NCIA-------------------*/

void initTable(unsigned int tab[])
{
    for (int i = 0; i < TAM; i++)
    {
        tab[i] = 0;
    }
}

void fillFreqTable(unsigned char strData[], unsigned int tab[])
{
    int i = 0;
    while (strData[i] != '\0')
    {
        tab[strData[i]]++;
        i++;
    }
}

void printFreqTable(unsigned int tab[])
{
    int i;
    printf("\tTABELA DE FREQU�NCIA\n");
    for (i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            printf("\t %d - %u - %c\n", i, tab[i], i);
        }
    }
}

/*---------------------PARTE 2: list ENCADEADA ORDENADA---------------*/

void createList(list *list)
{
    list->start = NULL;
    list->tam = 0;
}

void insertInOrder(list *list, node *newNode)
{
    node *aux = NULL;

    if (list->start == NULL)
    {
        list->start = newNode;
    }
    else if (newNode->freq < list->start->freq)
    {
        newNode->next = list->start;
        list->start = newNode;
    }
    else
    {
        aux = list->start;
        while (aux->next && aux->next->freq <= newNode->freq)
        {
            aux = aux->next;
        }
        newNode->next = aux->next;
        aux->next = newNode;
    }

    list->tam++;
}

void fillList(unsigned int tab[], list *list)
{
    int i;
    node *newNode;

    for (i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            newNode = malloc(sizeof(node));
            if (newNode)
            {
                newNode->ch = i;
                newNode->freq = tab[i];
                newNode->right = newNode->left = newNode->next = NULL;

                insertInOrder(list, newNode);
            }
            else
            {
                printf("\tErro! ao Alocar mem�ria em fillList!\n");
                break;
            }
        }
    }
}

void printList(list *list)
{
    node *aux = list->start;
    printf("\tlist Ordenada: Tamanho: %d\n", list->tam);

    while (aux)
    {
        printf("\tCharacter: %c Frequ�ncia: %d\n", aux->ch, aux->freq);
        aux = aux->next;
    }
}

/*---------------------PARTE 3: Montar �rvore de  Huffman ---------------*/

node *removeNodeFromStart(list *list)
{
    node *aux = NULL;

    if (list->start)
    {
        aux = list->start;
        list->start = aux->next;
        aux->next = NULL;
        list->tam--;
    }

    return aux;
}

node *mountHuffmanTree(list *list)
{
    node *first, *second, *newNode;
    while (list->tam > 1)
    {
        first = removeNodeFromStart(list);
        second = removeNodeFromStart(list);
        newNode = malloc(sizeof(node));

        if (newNode)
        {
            newNode->ch = '+'; /*Opcional esse preenchimento*/
            newNode->freq = first->freq + second->freq;
            newNode->left = first;
            newNode->right = second;
            newNode->next = NULL;

            insertInOrder(list, newNode);
        }
        else
        {
            printf("\n\tErro! ao alocar mem�ria em mountHuffmanTree!\n");
            break;
        }
    }

    return list->start;
}

void printHuffmanTree(node *centralNode, int tam)
{
    if (centralNode->left == NULL && centralNode->right == NULL)
    {
        printf("\tFolha: %c\t Altura: %d\n", centralNode->ch, tam);
    }
    else
    {
        printHuffmanTree(centralNode->left, tam + 1);
        printHuffmanTree(centralNode->right, tam + 1);
    }
}

/*---------------------PARTE 4: Montar o Dicion�rio ---------------*/

int huffmanTreeHeight(node *centralNode)
{
    int left, right;

    if (centralNode == NULL)
    {
        return -1;
    }
    else
    {
        left = huffmanTreeHeight(centralNode->left) + 1;
        right = huffmanTreeHeight(centralNode->right) + 1;

        if (left > right)
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}

/*
 *
 */

char **allocateDictionary(int columns)
{
    char **dictionary;
    int i;

    dictionary = malloc(sizeof(char *) * TAM);

    for (i = 0; i < TAM; i++)
    {
        dictionary[i] = calloc(columns, sizeof(char));
    }

    return dictionary;
}

/*
 */

void generateDictionary(char **dictionary, node *centralNode, char *way, int columns)
{
    char left[columns], right[columns];

    if (centralNode->left == NULL && centralNode->right == NULL)
    {
        strcpy(dictionary[centralNode->ch], way);
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

/*
 Matriz de caracteres
 */
void printDictionary(char **dictionary)
{
    printf("\t\nDicionário:\n");
    for (int i = 0; i < TAM; i++)
    {
        if (strlen(dictionary[i]) > 0)
            printf("\t%3d: %s\n", i, dictionary[i]);
    }
}

/*--------------------- PARTE 5: Codificar ----------------------------------*/
int calculateStringSize(char **dictionary, unsigned char *strData)
{
    int i = 0, tam = 0;
    while (strData[i] != '\0')
    {
        tam = tam + strlen(dictionary[strData[i]]);
        i++;
    }

    return tam + 1;
}

char *encode(char **dictionary, unsigned char *strData)
{

    int i = 0, tam = calculateStringSize(dictionary, strData);

    char *codigo = calloc(tam, sizeof(char));

    while (strData[i] != '\0')
    {
        strcat(codigo, dictionary[strData[i]]);
        i++;
    }

    return codigo;
}

/*--------------------- PARTE 6: Descodificar ----------------------------------*/
char *decode(unsigned char strData[], node *centralNode)
{
    int i = 0;
    node *aux = centralNode;
    char temp[2];
    char *descodificado = calloc(strlen(strData), sizeof(char));

    while (strData[i] != '\0')
    {
        if (strData[i] == '0')
        {
            aux = aux->left;
        }
        else
        {
            aux = aux->right;
        }

        if (aux->left == NULL && aux->right == NULL)
        {
            temp[0] = aux->ch;
            temp[1] = '\0';
            strcat(descodificado, temp);
            aux = centralNode;
        }

        i++;
    }

    return descodificado;
}

/*--------------------- PARTE 7: Compactar----------------------------------*/
void compact(unsigned char str[])
{
    FILE *file = fopen("./compressed/compacted.wg", "wb");

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

        fclose(file);
    }
    else
    {
        printf("\nErro ao Abrir/Criar file em compact\n");
    }
}

/*--------------------- PARTE 8: Descompactar----------------------------------*/
unsigned int verifyBit(unsigned char byte, int i)
{
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

void uncompact(node *centralNode)
{
    FILE *file = fopen("./compressed/compacted.wg", "rb");
    node *aux = centralNode;
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
                    printf("%c", aux->ch);
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

/*---------------------------------------------------------------------*/
int findSize()
{
    FILE *arq = fopen("./input.txt", "r");
    int tam = 0;

    if (arq)
    {
        while (fgetc(arq) != -1)
        {
            tam++;
        }
        fclose(arq);
    }
    else
    {
        printf("\nErro ao Abrir file em findSize\n");
    }
    return tam;
}

void readText(unsigned char *strData)
{
    FILE *arq = fopen("./input.txt", "r");
    char letra;
    int i = 0;

    if (arq)
    {
        while (!feof(arq))
        {
            letra = fgetc(arq);
            if (letra != -1)
            {
                strData[i] = letra;
                i++;
            }
        }
        fclose(arq);
    }
    else
    {
        printf("\nErro ao Abrir file em readText\n");
    }
}

void readEncodedText(unsigned char *strData)
{
    FILE *arq = fopen("./input.txt", "r");
    char letra;
    int i = 0;

    if (arq)
    {
        while (!feof(arq))
        {
            letra = fgetc(arq);
            if (letra != -1)
            {
                strData[i] = letra;
                i++;
            }
        }
        fclose(arq);
    }
    else
    {
        printf("\nErro ao Abrir file em readText\n");
    }
}

// Função para salvar a tabela de frequencia em um arquivo
void saveTable(unsigned int tab[])
{
    FILE *file = fopen("./compressed/.temp.txt", "w");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    for (int i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            fprintf(file, "%d - %d\n", i, tab[i]);
        }
    }

    fclose(file);
}

// Função para ler o dicionário de um arquivo
void readTable(unsigned int tab[])
{

    FILE *file = fopen("./compressed/.temp.txt", "r");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    int key;
    int freq;

    while (fscanf(file, "%d - %d\n", &key, &freq) != EOF)
        tab[key] = freq;

    fclose(file);
}