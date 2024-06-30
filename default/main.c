#include <stdio.h>
#include <stdlib.h>
#include "Comprimir_Descomprimir.h"
#include <windows.h> // Para SetConsoleOutput
#define TAM 256

int main()
{

    SetConsoleOutputCP(65001);

    unsigned char *texto;
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    int colunas, tam;
    char **dicionario;
    char *codificado, *descodificado;

    /*Para Alterar a formatação de texto do prompt de comando(CMD)
    para aceitar a acentua��o.
    */

    tam = descobrir_tamanho();
    printf("\nQuantidade: %d\n", tam);

    texto = calloc(tam * 2, sizeof(unsigned char));
    ler_texto(texto);
    printf("\nTEXTO:\n%s\n", texto);

    /*--------------------- PARTE 1: TABELA DE FREQUNCIA----------------------*/

    inicializar_tabela(tabela_frequencia);
    preencher_tab_frequencia(texto, tabela_frequencia);
    imprimir_tab_frequencia(tabela_frequencia);
    return 0;

    /*--------------------- PARTE 2: LISTA ENCADEADA ORDENADA-------------------*/

    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    imprimir_lista(&lista);
    return 0;

    /*--------------------- PARTE 3: Montar �rvore de  Huffman -----------------*/
    arvore = montar_arvore(&lista);
    printf("Arvore de Ruffman\n");
    imprimir_arvore(arvore, 0);

    /*--------------------- PARTE 4: Montar o Dicion�rio ------------------------*/
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    imprimir_dicionario(dicionario);

    /*--------------------- PARTE 5: Codificar ----------------------------------*/
    codificado = codificar(dicionario, texto);
    printf("\n\tTexto codificado: %s\n", codificado);

    /*--------------------- PARTE 6: Decodificar ----------------------------------*/
    descodificado = descodificar(codificado, arvore);
    printf("\n\tTexto descodificado: %s\n", descodificado);

    /*--------------------- PARTE 7: Compactar----------------------------------*/
    compactar(codificado);

    /*--------------------- PARTE 8: Descompactar----------------------------------*/
    printf("\nARQUIVO DESCOMPACTADO!\n");
    descompactar(arvore);
    printf("\n\n");

    free(texto);
    free(codificado);
    free(descodificado);
    return 0;
}
