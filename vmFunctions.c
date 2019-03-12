#include <stdio.h>
#include "vmFunctions.h"

vmTable* createVMTable(int len){
  vmTable new_table = malloc(sizeof(vmTable));  //
  // Page numbers are Index
  // Frame numbers are inside
  new_table -> frameNumberArray = malloc(sizeof(short) * len);

  // Filling page numbers
  // If it is unallocated its number should just be 0
  for(int i = 0; i < length; i++){
    new_table -> frameNumberArray[i] = 0;
  }

  return new_table;
}

void freeVMtable(vmTable** table){
  free((*table) -> frameNumberArray);
  free(*table);
}

void displayTable(vmTable** viewTable){
  printf("\n******************* START PRINT TABLE *******************\n");
  for(int i = 0; i < (*viewTable)->length; i++){
    printf("Page Number = %h\tFrame number = %h\n" (*viewTable)->pageNumberArray[i], (*viewTable)-> frameNumberArray[i]);
  }
  printf("\n******************* END PRINT TABLE *******************\n");
}



short getPageNumber(short mask, short value, short shift){
  return((value & mask)>>shift);
}
short getOffset(short mask, short value){
  return value & mask;
}
