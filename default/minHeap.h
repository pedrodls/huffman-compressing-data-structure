
// Estrutura do nó da árvore de Huffman
typedef struct MinHeapNode MinHeapNode;

// Estrutura da min-heap (min-árvore)
typedef struct MinHeap MinHeap;

// Estrutura para armazenar os códigos de Huffman
typedef struct HuffmanCode HuffmanCode;

//Função para criar um nó
MinHeapNode *newNode(unsigned char data, unsigned freq);

//Função que cria um MinHeap
MinHeap *createMinHeap(unsigned capacity);

//Função que faz a troca de nós em minHeap
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b);

//Função que garante a formação de uma minHeap
void minHeapify(MinHeap *minHeap, int idx);

//Função que verifica se o tamanho da minHeap é 1
int isSizeOne(MinHeap *minHeap);

//Função que extrai um nó mínimo na minHeap
MinHeapNode *extractMin(MinHeap *minHeap);

//Função que insere um novo nó em um minHeap
void insertMinHeap(MinHeap *minHeap, MinHeapNode *minHeapNode);

//Função que cria um minHeap
void buildMinHeap(MinHeap *minHeap);

//Função que imprime o texto a ser compressado
void printArr(int arr[], int n);

//Função que verifica se um nó é folha
int isLeaf(MinHeapNode *root);

//Função que um MinHeap
MinHeap *createAndBuildMinHeap(char data[], int freq[], int size);

//Função que cria a árvore de Huffman
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);

//Função que escreve os códigos binários
void printCodes(MinHeapNode* root, int arr[], int top, HuffmanCode *codes, int *index);

//Função que gera códigos binários
void HuffmanCodes(char data[], int freq[], int size, HuffmanCode *codes);

//Função que gera compressão de ficheiro
void compressFile(const char* inputFilename, const char* outputFilename, HuffmanCode* codes, int numCodes);

//Função que gera descompressão de ficheiro
void decompressFile(const char* inputFilename, const char* outputFilename);

// Função auxiliar para liberar nós da árvore
void freeTree(MinHeapNode *node);
