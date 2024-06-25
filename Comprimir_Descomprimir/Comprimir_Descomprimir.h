#ifndef COMPRIMIR_DESCOMPRIMIR_H
#define COMPRIMIR_DESCOMPRIMIR_H

/*--------------------- PARTE 1: TABELA DE FREQUÊNCIA----------------------*/

typedef struct no {
    unsigned char caracter;
    int frequencia;
    struct no *esq, *dir, *proximo;
}No;

typedef struct lista {
    No *inicio;
    int tam;
}Lista;


// Inicializa a tabela com zeros
void inicializar_tabela(unsigned int tab[]);

// Preenche a tabela de frequência
void preencher_tab_frequencia(unsigned char texto[], unsigned int tab[]);

// Imprime a tabela de frequência
void imprimir_tab_frequencia(unsigned int tab[]);

/*---------------------PARTE 2: LISTA ENCADEADA ORDENADA---------------*/

// Inicializa a lista encadeada
void criar_lista(Lista *lista);

// Insere um nó na lista de forma ordenada por frequência
void inserir_ordenado(Lista *lista, No *no);

// Preenche a lista com os dados da tabela de frequência
void preencher_lista(unsigned int tab[], Lista *lista);

// Imprime os elementos da lista ordenada
void imprimir_lista(Lista *lista);

/*---------------------PARTE 3: Montar Árvore de  Huffman ---------------*/

No *remove_no_inicio(Lista *lista);
No *montar_arvore(Lista *lista);
void imprimir_arvore(No *raiz, int tam);

/*---------------------PARTE 4: Montar o Dicionário ----------------------*/

int altura_arvore(No *raiz);
char** aloca_dicionario(int colunas);
void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas);
void imprimir_dicionario(char **dicionario);

/*--------------------- PARTE 5: Codificar ----------------------------------*/
int calcular_tamanho_string(char **dicionario,unsigned char *texto);
char *codificar(char **dicionario, unsigned char *texto);

/*--------------------- PARTE 6: Decodificar ----------------------------------*/
char *descodificar(unsigned char texto[], No *raiz);

/*--------------------- PARTE 7: Compactar----------------------------------*/
void compactar(unsigned char str[]);

/*--------------------- PARTE 8: Descompactar----------------------------------*/
unsigned int verificar_bit(unsigned char byte, int i);
void descompactar(No *raiz);
/*-----------------------------------------------------------------------------
*/
int descobrir_tamanho();
void ler_texto(unsigned char *texto);

#endif //COMPRIMIR_DESCOMPRIMIR_H
