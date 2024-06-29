
// Estrutura do nó da árvore de Huffman
typedef struct huffmanNode HuffmanNode;

// Função para criar um novo nó de Huffman
HuffmanNode *createNode(char character, int frequency);

// Função para pegar a frequência
int getFrequency(HuffmanNode *node);

// Função para pegar a frequência
HuffmanNode *getLeft(HuffmanNode *node);

// Função para pegar a frequência
HuffmanNode *getRight(HuffmanNode *node);

// Função para pegar o caracter
char getCharacter(HuffmanNode *node);

// Função para construir a árvore de Huffman
HuffmanNode *buildHuffmanTree(char data[], int freq[], int size);

// Função para verificar se um nó é uma folha
int isLeaf(HuffmanNode *root);

// Função para armazenar os códigos de Huffman em um array
void storeCodes(HuffmanNode *root, int arr[], int top, int **codes, int *lengths);

// Função para imprimir os códigos dos caracteres
void printCodes(HuffmanNode *root, int *arr, int top);

// Função principal para construir a árvore de Huffman e gerar os códigos
void HuffmanCodes(char data[], int freq[], int size, int **codes, int *lengths);