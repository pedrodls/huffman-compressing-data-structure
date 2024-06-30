#include "Comprimir_Descomprimir.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 256

/*---------------------------------PARTE 1: TABELA DE FREQU�NCIA-------------------*/

void inicializar_tabela(unsigned int tab[])
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        tab[i] = 0;
    }
}

void preencher_tab_frequencia(unsigned char texto[], unsigned int tab[])
{
    int i = 0;
    while (texto[i] != '\0')
    {
        tab[texto[i]]++;
        i++;
    }
}

void imprimir_tab_frequencia(unsigned int tab[])
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

/*---------------------PARTE 2: LISTA ENCADEADA ORDENADA---------------*/

void criar_lista(Lista *lista)
{
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no)
{
    No *aux = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = no;
    }
    else if (no->frequencia < lista->inicio->frequencia)
    {
        no->proximo = lista->inicio;
        lista->inicio = no;
    }
    else
    {
        aux = lista->inicio;
        while (aux->proximo && aux->proximo->frequencia <= no->frequencia)
        {
            aux = aux->proximo;
        }
        no->proximo = aux->proximo;
        aux->proximo = no;
    }

    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista)
{
    int i;
    No *novo;

    for (i = 0; i < TAM; i++)
    {
        if (tab[i] > 0)
        {
            novo = malloc(sizeof(No));
            if (novo)
            {
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->dir = novo->esq = novo->proximo = NULL;

                inserir_ordenado(lista, novo);
            }
            else
            {
                printf("\tErro! ao Alocar mem�ria em preencher_lista!\n");
                break;
            }
        }
    }
}

void imprimir_lista(Lista *lista)
{
    No *aux = lista->inicio;
    printf("\tLista Ordenada: Tamanho: %d\n", lista->tam);

    while (aux)
    {
        printf("\tCharacter: %c Frequ�ncia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->proximo;
    }
}

/*---------------------PARTE 3: Montar �rvore de  Huffman ---------------*/

No *remove_no_inicio(Lista *lista)
{
    No *aux = NULL;

    if (lista->inicio)
    {
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tam--;
    }

    return aux;
}

No *montar_arvore(Lista *lista)
{
    No *primeiro, *segundo, *novo;
    while (lista->tam > 1)
    {
        primeiro = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        novo = malloc(sizeof(No));

        if (novo)
        {
            novo->caracter = '+'; /*Opcional esse preenchimento*/
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->proximo = NULL;

            inserir_ordenado(lista, novo);
        }
        else
        {
            printf("\n\tErro! ao alocar mem�ria em montar_arvore!\n");
            break;
        }
    }

    return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam)
{
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        printf("\tFolha: %c\t Altura: %d\n", raiz->caracter, tam);
    }
    else
    {
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}

/*---------------------PARTE 4: Montar o Dicion�rio ---------------*/

int altura_arvore(No *raiz)
{
    int esq, dir;

    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        esq = altura_arvore(raiz->esq) + 1;
        dir = altura_arvore(raiz->dir) + 1;

        if (esq > dir)
        {
            return esq;
        }
        else
        {
            return dir;
        }
    }
}

/*
 *
 */

char **aloca_dicionario(int colunas)
{
    char **dicionario;
    int i;

    dicionario = malloc(sizeof(char *) * TAM);

    for (i = 0; i < TAM; i++)
    {
        dicionario[i] = calloc(colunas, sizeof(char));
    }

    return dicionario;
}

/*
 */

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas)
{
    char esquerda[colunas], direita[colunas];

    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        strcpy(dicionario[raiz->caracter], caminho);
    }
    else
    {
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
void imprimir_dicionario(char **dicionario)
{
    int i;
    printf("\t\nDicion�rio:\n");
    for (i = 0; i < TAM; i++)
    {
        if (strlen(dicionario[i]) > 0)
            printf("\t%3d: %s\n", i, dicionario[i]);
    }
}

/*--------------------- PARTE 5: Codificar ----------------------------------*/
int calcular_tamanho_string(char **dicionario, unsigned char *texto)
{
    int i = 0, tam = 0;
    while (texto[i] != '\0')
    {
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }

    return tam + 1;
}

char *codificar(char **dicionario, unsigned char *texto)
{

    int i = 0, tam = calcular_tamanho_string(dicionario, texto);

    char *codigo = calloc(tam, sizeof(char));

    while (texto[i] != '\0')
    {
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }

    return codigo;
}

/*--------------------- PARTE 6: Descodificar ----------------------------------*/
char *descodificar(unsigned char texto[], No *raiz)
{
    int i = 0;
    No *aux = raiz;
    char temp[2];
    char *descodificado = calloc(strlen(texto), sizeof(char));

    while (texto[i] != '\0')
    {
        if (texto[i] == '0')
        {
            aux = aux->esq;
        }
        else
        {
            aux = aux->dir;
        }

        if (aux->esq == NULL && aux->dir == NULL)
        {
            temp[0] = aux->caracter;
            temp[1] = '\0';
            strcat(descodificado, temp);
            aux = raiz;
        }

        i++;
    }

    return descodificado;
}

/*--------------------- PARTE 7: Compactar----------------------------------*/
void compactar(unsigned char str[])
{
    FILE *arquivo = fopen("compactado.wg", "wb");
    int i = 0, j = 7;
    unsigned char mascara, byte = 0;

    if (arquivo)
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
                fwrite(&byte, sizeof(unsigned char), 1, arquivo);
                byte = 0;
                j = 7;
            }
            i++;
        }

        if (j != 7)
        {
            fwrite(&byte, sizeof(unsigned char), 1, arquivo);
        }

        fclose(arquivo);
    }
    else
    {
        printf("\nErro ao Abrir/Criar arquivo em compactar\n");
    }
}

/*--------------------- PARTE 8: Descompactar----------------------------------*/
unsigned int verificar_bit(unsigned char byte, int i)
{
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

void descompactar(No *raiz)
{
    FILE *arquivo = fopen("compactado.wg", "rb");
    No *aux = raiz;
    unsigned char byte;
    int i;

    if (arquivo)
    {
        while (fread(&byte, sizeof(unsigned char), 1, arquivo))
        {
            for (i = 7; i >= 0; i--)
            {
                if (verificar_bit(byte, i))
                {
                    aux = aux->dir;
                }
                else
                {
                    aux = aux->esq;
                }
                if (aux->esq == NULL && aux->dir == NULL)
                {
                    printf("%c", aux->caracter);
                    aux = raiz;
                }
            }
        }
        fclose(arquivo);
    }
    else
    {
        printf("\nErro ao Abrir arquivo em descompactar\n");
    }
}

/*---------------------------------------------------------------------*/
int descobrir_tamanho()
{
    FILE *arq = fopen("teste.txt", "r");
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
        printf("\nErro ao Abrir arquivo em descobrir_tamanho\n");
    }
    return tam;
}

void ler_texto(unsigned char *texto)
{
    FILE *arq = fopen("teste.txt", "r");
    char letra;
    int i = 0;

    if (arq)
    {
        while (!feof(arq))
        {
            letra = fgetc(arq);
            if (letra != -1)
            {
                texto[i] = letra;
                i++;
            }
        }
        fclose(arq);
    }
    else
    {
        printf("\nErro ao Abrir arquivo em ler_texto\n");
    }
}