#include <stdio.h>
#include <locale.h>
#include <string.h>
#include "Comprimir_Descomprimir.h"
#define TAM 256


int main() {
    setlocale(LC_ALL, "Portuguese");

    unsigned char texto[] = "Vamos aprender programação";
    unsigned int tabela_frequencia[TAM];

    Lista lista;
    No *arvore;
    int colunas;
    char **dicionario;

    /*---------------------------------PARTE 1: TABELA DE FREQUÊNCIA-------------------*/

    inicializar_tabela(tabela_frequencia);
    preencher_tab_frequencia(texto, tabela_frequencia);
    imprimir_tab_frequencia(tabela_frequencia);

    /*--------------------- PARTE 2: LISTA ENCADEADA ORDENADA---------------*/

    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    imprimir_lista(&lista);

    /*--------------------- PARTE 3: Montar Árvore de  Huffman ---------------*/
    arvore = montar_arvore(&lista);
    printf("\n\tÁrvore de Ruffman\n");
    imprimir_arvore(arvore, 0);

    /*--------------------- PARTE 4: Montar o Dicionário ---------------*/
    colunas = altura_arvore(arvore) + 1;
    dicionario = aloca_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    imprimir_dicionario(dicionario);
    return 0;
}
