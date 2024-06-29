
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
void fillList(unsigned int freq[], HuffmanList *list);

// Função para imprimir a lista
void printList(HuffmanList *list);

