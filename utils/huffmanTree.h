

// Estrutura do nó da árvore de Huffman
typedef struct huffmanNode HuffmanNode;

// Função para criar um novo nó de Huffman
HuffmanNode *createNode(char character, int frequency);

// Função para pegar a frequência
int getFrequency(HuffmanNode *node);

// Função para construir a árvore de Huffman
HuffmanNode *buildHuffmanTree(char *data, int *freq, int size);

// Função para imprimir os códigos dos caracteres
void printCodes(HuffmanNode *root, int *arr, int top);

// Função para pegar os códigos binários
void HuffmanCodes(char *data, int *freq, int size);
