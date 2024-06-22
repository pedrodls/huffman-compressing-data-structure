#include "Comprimir_Descomprimir.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 256

/*---------------------------------PARTE 1: TABELA DE FREQUÊNCIA-------------------*/

void inicializar_tabela(unsigned int tab[]) {
    int i;
    for (i = 0; i < TAM; i++) {
        tab[i] = 0;
    }
}

void preencher_tab_frequencia(unsigned char texto[], unsigned int tab[]) {
    int i = 0;
    while (texto[i] != '\0') {
        tab[texto[i]]++;
        i++;
    }
}

void imprimir_tab_frequencia(unsigned int tab[]) {
    int i;
    printf("\tTABELA DE FREQUÊNCIA\n");
    for (i = 0; i < TAM; i++) {
        if (tab[i] > 0) {
            printf("\t %d - %u - %c\n", i, tab[i], i);
        }
    }
}

/*---------------------PARTE 2: LISTA ENCADEADA ORDENADA---------------*/

void criar_lista(Lista *lista) {
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no) {
    No *aux = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = no;
    }
    else if (no->frequencia < lista->inicio->frequencia) {
        no->proximo = lista->inicio;
        lista->inicio = no;
    }
    else {
        aux = lista->inicio;
        while (aux->proximo && aux->proximo->frequencia <= no->frequencia) {
            aux = aux->proximo;
        }
        no->proximo = aux->proximo;
        aux->proximo = no;
    }

    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista) {
    int i;
    No *novo;

    for (i = 0; i < TAM; i++) {
        if (tab[i] > 0) {
            novo = malloc(sizeof(No));
            if (novo) {
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = novo->esq = novo->proximo = NULL;

                inserir_ordenado(lista, novo);
            }
            else {
                printf("\tErro! ao Alocar memória em preencher_lista!\n");
                break;
            }
        }
    }
}

void imprimir_lista(Lista *lista) {
    No *aux = lista->inicio;
    printf("\tLista Ordenada: Tamanho: %d\n", lista->tam);

    while (aux) {
        printf("\tCharacter: %c Frequência: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

/*---------------------PARTE 3: Montar Árvore de  Huffman ---------------*/

No *remove_no_inicio(Lista *lista) {
    No *aux = NULL;

    if(lista->inicio) {
            aux = lista->inicio;
            lista->inicio = aux->proximo;
            aux->proximo = NULL;
            lista->tam--;
    }

    return aux;
}

No *montar_arvore(Lista *lista) {
    No *primeiro, *segundo, *novo;
    while(lista->tam > 1) {
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if (novo) {
            novo->caracter = '+'; /*Opcional esse preenchimento*/
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);
        }else {
            printf("\n\tErro! ao alocar memória em montar_arvore!\n");
            break;
        }
    }

    return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam) {
    if (raiz->esq == NULL && raiz->dir == NULL) {
        printf("\tFolha: %c\tAltura: %d\n", raiz->caracter, tam);
    }else {
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}

/*---------------------PARTE 4: Montar o Dicionário ---------------*/

int altura_arvore(No *raiz) {
    int esq, dir;

    if(raiz == NULL) {
        return -1;
    }else {
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if(esq > dir) {
            return esq;
        }else {
            return dir;
        }
    }
}

/*
 *
 */

char** aloca_dicionario(int colunas) {
    char **dicionario;
    int i;

    dicionario = malloc(sizeof(char*) * TAM);

    for (i=0; i < TAM; i++) {
        dicionario[i] = calloc(colunas, sizeof(char));
    }

    return dicionario;
}

/*
 */

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas) {
    char esquerda[colunas], direita[colunas];

    if(raiz->esq == NULL && raiz->dir == NULL) {
        strcpy(dicionario[raiz->caracter], caminho);
    }else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

/*
 Matriz de caracteres
 */
void imprimir_dicionario(char **dicionario) {
    int i;
    printf("\t\nDicionário:\n");
    for (i=0; i < TAM; i++) {
        if (strlen(dicionario[i]) > 0)
            printf("\t%3d: %s\n", i, dicionario[i]);
    }
}

/*--------------------- PARTE 5: Codificar ----------------------------------*/
int calcular_tamanho_string(char **dicionario, char *texto) {
    int i = 0, tam = 0;
    while (texto[i] != '\0') {
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }

    return tam + 1;
}

char *codificar(char **dicionario, unsigned char *texto) {

    int i = 0, tam = calcular_tamanho_string(dicionario, texto);

    char *codigo = calloc(tam, sizeof(char));

    while (texto[i] != '\0') {
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }

    return codigo;
}

