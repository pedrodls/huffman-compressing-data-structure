#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./utils.h"

// Definindo o número máximo de caracteres possíveis (ASCII)
#define CHAR_SIZE 256

// Função para preencher o array de dados com caracteres únicos do texto
void fillFrequencieArray(char data[], int freq[], int dataSize)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (freq[i] > 0)
        {
            data[dataSize] = i;
            dataSize++;
        }
    }
}

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
