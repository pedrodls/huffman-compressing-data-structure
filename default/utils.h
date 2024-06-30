#define TAM 256

//Função para pegar o comprimento do ficheiro
int findSize();

//Funcão para ler ficheiro
void readText(unsigned char *strData);

//Função para inicializar a tabela de frequência
void initTable(unsigned int tab[]);

//Função para preencher a tabela de frequência
void fillFreqTable(unsigned char strData[], unsigned int tab[]);

//Função para imprimir a tabela de frequência
void printFreqTable(unsigned int tab[]);