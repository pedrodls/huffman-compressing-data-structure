#include <stdio.h>
#include <stdlib.h>
#define TAM 256

//Função para pegar o comprimento do ficheiro
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

//Funcão para ler ficheiro
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

//Função para inicializar a tabela de frequência
void initTable(unsigned int tab[])
{
    for (int i = 0; i < TAM; i++)
    {
        tab[i] = 0;
    }
}

//Função para preencher a tabela de frequência
void fillFreqTable(unsigned char strData[], unsigned int tab[])
{
    int i = 0;
    while (strData[i] != '\0')
    {
        tab[strData[i]]++;
        i++;
    }
}

//Função para imprimir a tabela de frequência
void printFreqTable(unsigned int tab[])
{
    int i;
    printf("\tTABELA DE FREQUêNCIA\n");
    for (i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            printf("\t %d - %u - %c\n", i, tab[i], i);
        }
    }
}