#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./utils.h"

// Definindo o número máximo de caracteres possíveis (ASCII)
#define CHAR_SIZE 256

// Função para calcular as frequências dos caracteres em um arquivo
void calculateFrequencies(const char *inputFileName, int freq[])
{

    setlocale(LC_ALL, "Portuguese");
    // Inicializar o array de frequências
    for (int i = 0; i < 256; i++)
    {
        freq[i] = 0;
    }

    // Abrir o arquivo de entrada
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile)
    {
        perror("Erro ao abrir o arquivo de entrada");
        return;
    }

    // Ler o conteúdo do arquivo e calcular as frequências
    int c;
    while ((c = fgetc(inputFile)) != EOF)
    {
        freq[(unsigned char)c]++;
    }

    fclose(inputFile);
}

// Função para pegar o tamanho do ficheiro
int getFileSize()
{
    FILE *file = fopen("./input.txt", "r");
    int tam = 0;

    if (file)
    {
        while (fgetc(file) != -1)
        {
            tam++;
        }
        fclose(file);
    }
    else
    {
        printf("\nErro ao Abrir arquivo em descobrir_tamanho\n");
    }
    return tam;
}

// Função para pegar o data do ficheiro
void readFileText(unsigned char *data)
{
    FILE *file = fopen("input.txt", "r");
    char letter;
    int i = 0;

    if (file)
    {
        while (!feof(file))
        {
            letter = fgetc(file);
            if (letter != -1)
            {
                data[i] = letter;
                i++;
            }
        }
        fclose(file);
    }
    else
    {
        printf("\nErro ao Abrir arquivo em ler_texto\n");
    }

}

//Função para inicializar a tabela de frequência
void initFrequencyTab(unsigned int tab[])
{
    for (int i = 0; i < CHAR_SIZE; i++)
        tab[i] = 0;
}

//Função para preencher a tabela de frequência
void fillFrequencyTab(unsigned char data[], unsigned int tab[])
{
    int i = 0;
    while (data[i] != '\0')
    {
        tab[data[i]]++;
        i++;
    }
}

//Função para imprimir a tabela de frequência
void printTabFrequency(unsigned int tab[])
{
    
    printf("\tTABELA DE FREQUÊNCIA\n");
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (tab[i] > 0)
        {
            printf("\t %d - %u - %c\n", i, tab[i], i);
        }
    }
}

