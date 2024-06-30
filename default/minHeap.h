
// Estrutura do nó da árvore de Huffman
typedef struct MinHeapNode MinHeapNode;

// Estrutura da min-heap (min-árvore)
typedef struct MinHeap MinHeap;

// Estrutura para armazenar os códigos de Huffman
typedef struct HuffmanCode HuffmanCode;

MinHeapNode *newNode(unsigned char data, unsigned freq);

MinHeap *createMinHeap(unsigned capacity);

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b);

void minHeapify(MinHeap *minHeap, int idx);

int isSizeOne(MinHeap *minHeap);

MinHeapNode *extractMin(MinHeap *minHeap);

void insertMinHeap(MinHeap *minHeap, MinHeapNode *minHeapNode);

void buildMinHeap(MinHeap *minHeap);

void printArr(int arr[], int n);

int isLeaf(MinHeapNode *root);

MinHeap *createAndBuildMinHeap(char data[], int freq[], int size);

MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);

void printCodes(MinHeapNode* root, int arr[], int top, HuffmanCode *codes, int *index);

void HuffmanCodes(char data[], int freq[], int size, HuffmanCode *codes);


void compressFile(const char* inputFilename, const char* outputFilename, HuffmanCode* codes, int numCodes);

void decompressFile(const char* inputFilename, const char* outputFilename);

// Função auxiliar para liberar nós da árvore
void freeTree(MinHeapNode *node);
