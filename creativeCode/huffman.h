
// Estrutura do nó da árvore de Huffman
typedef struct huffmanNode HuffmanNode;

// Estrutura da lista ordenada
typedef struct huffmanList HuffmanList;

// Função para inicializar a lista
HuffmanList *initList(HuffmanList *list);

// Função para inicializar no
HuffmanNode *initNewHuffmanNode();

// Função para inserir na lista de forma ordenada
void insertInOrderList(HuffmanList *list, HuffmanNode *node);

// Função para inserir os dados provienientes da tabela de frequência
void fillList(int freq[], HuffmanList *list);

// Função para imprimir a lista
void printList(HuffmanList *list);

// Função para criar a árvore de huffman
HuffmanNode *buildHuffmanTree(HuffmanList *myList);

// Função para remover um nó
HuffmanNode *removeFromStart(HuffmanList *list);

//Função para imprimir a árvore
void printHuffmanTree(HuffmanNode *cetralNode, int size);

//Função para alocar de forma dinâmica o dicionário(Tabela)
char** allocateDictionary(int columns);

// Função para calcular a altura da árvore
int heightOfHuffmanTree(HuffmanNode *centralNode);

// Função para gerar dicionário
void generateDictionary(char **dictionary, HuffmanNode *centralNode, char *way, int columns);

//Função para imprimir o dicionário
void printDictionary(char **dictionary);

// Função para calcular o tamanho da String
int calculateStringSize(char **dictionary, unsigned char *text);

//Função para codificar a string
char *encodeString(char **dictionary, unsigned char *text);

//Função para decodificar a string
char *decodedString(unsigned char text[], HuffmanNode *centralNode);

//Função para compactar
void compact(unsigned char str[]);

// Função para descompactar
void decompact(HuffmanNode *centralNode);

// Função para verificar bit
unsigned int verifyBit(unsigned char byte, int i);