#include "./huffman.h"

// Definindo o número máximo de caracteres possíveis (ASCII)
#define CHAR_SIZE 256

// Função para calcular as frequências dos caracteres em um arquivo
void calculateFrequencies(const char *inputFileName, int freq[]);

//Função para pegar o tamanho do ficheiro
int getFileSize();

//Função para pegar o texto do ficheiro
void readFileText(unsigned char *data);

//Função para inicializar a tabela de frequência
void initFrequencyTab(unsigned int tab[]);

//Função para preencher a tabela de frequência
void fillFrequencyTab(unsigned char data[], unsigned int tab[]);

//Função para imprimir a tabela de frequência
void printTabFrequency(unsigned int tab[]);