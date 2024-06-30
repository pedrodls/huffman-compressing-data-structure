#define TAM 256

int findSize();

void readText(unsigned char *strData);

void initTable(unsigned int tab[]);

void fillFreqTable(unsigned char strData[], unsigned int tab[]);

void printFreqTable(unsigned int tab[]);