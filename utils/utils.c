#include <stdio.h>
#include <string.h>
#include "./utils.h"

#define MAX_CHAR 256 // Definindo o número máximo de caracteres possíveis (ASCII)

/* void calcularFrequencia(char *str, int freq[]) {

}
 */
/* int main() {
    char str[] = "exemplo de string para contagem de frequencia";
    int freq[MAX_CHAR];

    calcularFrequencia(str, freq);

    printf("Frequência dos caracteres na string:\n");
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] != 0) {
            printf("Caractere '%c' : %d vezes\n", i, freq[i]);
        }
    }

    return 0;
} */

void getFrequency(char *str, int freq[])
{
    // Inicializando o array de frequências com 0
    for (int i = 0; i < MAX_CHAR; i++)
        freq[i] = 0;

    // Percorrendo a string e contando a frequência de cada caractere
    for (int i = 0; str[i] != '\0'; i++)
        freq[(unsigned char)str[i]]++;
        
}
