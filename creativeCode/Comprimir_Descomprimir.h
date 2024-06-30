/*--------------------- PARTE 1: TABELA DE FREQUÊNCIA----------------------*/

typedef struct node
{
    unsigned char ch;
    int freq;
    struct node *left, *right, *next;
} node;

typedef struct list
{
    node *start;
    int tam;
} list;

// Inicializa a tabela com zeros
void initTable(unsigned int tab[]);

// Preenche a tabela de frequência
void fillFreqTable(unsigned char strData[], unsigned int tab[]);

// Imprime a tabela de frequência
void printFreqTable(unsigned int tab[]);

/*---------------------PARTE 2: list ENCADEADA ORDENADA---------------*/

// Inicializa a list encadeada
void createList(list *list);

// Insere um nó na list de forma ordenada por frequência
void insertInOrder(list *list, node *node);

// Preenche a list com os dados da tabela de frequência
void fillList(unsigned int tab[], list *list);

// Imprime os elementos da list ordenada
void printList(list *list);

/*---------------------PARTE 3: Montar Árvore de  Huffman ---------------*/
// Função para remover um nó no início 
node *removeNodeFromStart(list *list);

// Função para montar a árvore de huffman
node *mountHuffmanTree(list *list);

//Função para imprimir a árvore de huffman
void printHuffmanTree(node *centralNode, int tam);

/*---------------------PARTE 4: Montar o Dicionário ----------------------*/

// Função para calcular a altura da árvore de huffman
int huffmanTreeHeight(node *centralNode);

// Função para alocar dicionário
char **allocateDictionary(int columns);

// Função para gerar dicionário 
void generateDictionary(char **dictionary, node *centralNode, char *way, int columns);

// Função para imprimir um dicionário
void printDictionary(char **dictionary);

/*--------------------- PARTE 5: Codificar ----------------------------------*/

// Função para calcular o tamanho da string
int calculateStringSize(char **dictionary, unsigned char *strData);

//Função para codificar a string
char *encode(char **dictionary, unsigned char *strData);

/*--------------------- PARTE 6: Decodificar ----------------------------------*/
//Função para decodificar a string
char *decode(unsigned char strData[], node *centralNode);

/*--------------------- PARTE 7: Compactar----------------------------------*/
void compact(unsigned char str[]);

/*--------------------- PARTE 8: Descompactar----------------------------------*/
unsigned int verifyBit(unsigned char byte, int i);

void uncompact(node *centralNode);
/*-----------------------------------------------------------------------------
 */

//Função para buscar o tamanho do ficheiro
int findSize();

//Função para ler string do ficheiro 
void readText(unsigned char *strData);

// Função para salvar a tabela de frequencia em um arquivo
void saveTable(unsigned int tab[]);

// Função para ler o dicionário de um arquivo
void readTable(unsigned int tab[]);

//Função para ler a string codificada
void readEncodedText(unsigned char *strData);