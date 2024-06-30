#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

// Estrutura do nó da árvore de Huffman
typedef struct MinHeapNode
{
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

// Estrutura da min-heap (min-árvore)
typedef struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
} MinHeap;

// Estrutura para armazenar os códigos de Huffman
typedef struct HuffmanCode
{
    char character;
    char *code;
} HuffmanCode;

MinHeapNode *newNode(unsigned char data, unsigned freq)
{
    MinHeapNode *temp = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap *createMinHeap(unsigned capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(minHeap->capacity * sizeof(MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b)
{
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

MinHeapNode *extractMin(MinHeap *minHeap)
{
    MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap *minHeap, MinHeapNode *minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(MinHeapNode *root)
{
    return !(root->left) && !(root->right);
}

MinHeap *createAndBuildMinHeap(char data[], int freq[], int size)
{
    MinHeap *minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[data[i]]);

    minHeap->size = size;

    buildMinHeap(minHeap);

    return minHeap;
}

MinHeapNode *buildHuffmanTree(char data[], int freq[], int size)
{
    MinHeapNode *left, *right, *top;
    MinHeap *minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void printCodes(MinHeapNode *root, int arr[], int top, HuffmanCode *codes, int *index)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, codes, index);
    }

    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, codes, index);
    }

    if (isLeaf(root))
    {
        codes[*index].character = root->data;
        codes[*index].code = (char *)malloc(top + 1);
        for (int i = 0; i < top; ++i)
            codes[*index].code[i] = arr[i] + '0';
        codes[*index].code[top] = '\0';
        (*index)++;
    }
}

void HuffmanCodes(char data[], int freq[], int size, HuffmanCode *codes)
{
    struct MinHeapNode *root = buildHuffmanTree(data, freq, size);

    int arr[MAX_TREE_HT], top = 0, index = 0;

    printCodes(root, arr, top, codes, &index);
}

void compressFile(const char *inputFilename, const char *outputFilename, HuffmanCode *codes, int numCodes)
{
    FILE *inputFile = fopen(inputFilename, "r");
    FILE *outputFile = fopen(outputFilename, "w");

    if (!inputFile || !outputFile)
    {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    // Escrevendo a tabela de códigos no arquivo de saída
    fprintf(outputFile, "%d\n", numCodes);
    for (int i = 0; i < numCodes; i++)
    {
        fprintf(outputFile, "%c:%s\n", codes[i].character, codes[i].code);
    }

    char ch;
    while ((ch = fgetc(inputFile)) != EOF)
    {
        for (int i = 0; i < numCodes; i++)
        {
            if (codes[i].character == ch)
            {
                fputs(codes[i].code, outputFile);
                break;
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}

// Liberar memória da árvore de Huffman
// Função auxiliar para liberar nós da árvore
void freeTree(MinHeapNode *node)
{
    if (node)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

void decompressFile(const char *inputFilename, const char *outputFilename)
{
    FILE *inputFile = fopen(inputFilename, "r");
    FILE *outputFile = fopen(outputFilename, "w");
    if (!inputFile || !outputFile)
    {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    // Lendo a tabela de códigos do arquivo de entrada
    int numCodes;
    fscanf(inputFile, "%d\n", &numCodes);

    HuffmanCode *codes = (HuffmanCode *)malloc(numCodes * sizeof(HuffmanCode));
    for (int i = 0; i < numCodes; i++)
    {
        char buffer[256];
        fgets(buffer, sizeof(buffer), inputFile);
        codes[i].character = buffer[0];
        codes[i].code = strdup(buffer + 2);
        codes[i].code[strlen(codes[i].code) - 1] = '\0'; // Remover o '\n'
    }

    // Construindo a árvore de Huffman a partir da tabela de códigos
    MinHeapNode *root = newNode('$', 0);
    for (int i = 0; i < numCodes; i++)
    {
        MinHeapNode *currentNode = root;
        for (int j = 0; j < strlen(codes[i].code); j++)
        {
            if (codes[i].code[j] == '0')
            {
                if (!currentNode->left)
                {
                    currentNode->left = newNode('$', 0);
                }
                currentNode = currentNode->left;
            }
            else
            {
                if (!currentNode->right)
                {
                    currentNode->right = newNode('$', 0);
                }
                currentNode = currentNode->right;
            }
        }
        currentNode->data = codes[i].character;
    }

    // Descomprimindo o arquivo
    MinHeapNode *currentNode = root;
    char bit;
    while ((bit = fgetc(inputFile)) != EOF)
    {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        if (isLeaf(currentNode))
        {
            fputc(currentNode->data, outputFile);
            currentNode = root;
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    for (int i = 0; i < numCodes; i++)
    {
        free(codes[i].code); // Liberar memória alocada para cada código
    }

    free(codes); // Liberar memória alocada para a tabela de códigos

    freeTree(root);
}
