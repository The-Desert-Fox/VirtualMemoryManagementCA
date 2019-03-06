// Must define a page table class
// Must have functions to print to files
#ifndef vmFunctions
#define vmFunctions

typedef struct vmTable{
  int *pageNumberArray;
  int *frameNumberArray;
  int length;
}vmTable;

vmTable* createVMTable(int length);

// malloc used in createVMTable. free function would be useful
void freeVMtable(vmTable** t);

void displayTable(vmTable** viewTable);

void printFileTable(vmTable** printTable);

void displayPhysicalMemory(unsigned short int *physicalMemory[]);

// Every char is one byte. Just randomly make 2048 to 20480 that way.
void printPhysicalMemory(unsigned short int *physicalMemory[]);

short getPageNumber(short mask, short value, short shift);

short getOffset(short mask, short value);

#endif
