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

node *removeNodeFromStart(list *list);
node *mountHuffmanTree(list *list);
void printHuffmanTree(node *centralNode, int tam);

/*---------------------PARTE 4: Montar o Dicionário ----------------------*/

int huffmanTreeHeight(node *centralNode);
char **allocateDictionary(int columns);
void generateDictionary(char **dictionary, node *centralNode, char *way, int columns);
void printDictionary(char **dictionary);

/*--------------------- PARTE 5: Codificar ----------------------------------*/
int calculateStringSize(char **dictionary, unsigned char *strData);
char *encode(char **dictionary, unsigned char *strData);

/*--------------------- PARTE 6: Decodificar ----------------------------------*/
char *decode(unsigned char strData[], node *centralNode);

/*--------------------- PARTE 7: Compactar----------------------------------*/
void compact(unsigned char str[]);

/*--------------------- PARTE 8: Descompactar----------------------------------*/
unsigned int verifyBit(unsigned char byte, int i);

void uncompact(node *centralNode);
/*-----------------------------------------------------------------------------
 */
int findSize();
void readText(unsigned char *strData);

// Função para salvar a tabela de frequencia em um arquivo
void saveTable(unsigned int tab[]);

// Função para ler o dicionário de um arquivo
void readTable(unsigned int tab[]);