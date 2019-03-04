// Must define a page table class
// Must have functions to print to files
#ifndef vmFunctions
#define vmFunctions

typedef struct vmTable{
  // Whatever I need to define the table.
}vmTable;

vmTable* createVMTable(int length);

void displayTable(vmTable** viewTable);

void printFileTable(vmTable** printTable);

void displayPhysicalMemory(char[] physicalMemory);

// Every char is one byte. Just randomly make 2048 to 20480 that way.
void printPhysicalMemory(char[] physicalMemory);

#endif
