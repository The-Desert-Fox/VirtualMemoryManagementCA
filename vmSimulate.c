#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include "vmFunctions.h"

#define FRAME_SIZE	256
#define TOTAL_FRAMES	256
#define	PAGE_MASK	0xFF00
#define OFFSET_MASK	0x00FF
#define BITSHIFT	8
#define TLB_SIZE	16
#define PAGETABLE_SIZE	256

unsigned short* createVMTable(int len){
	// should be 2 * 256 = 512
	unsigned short* frameNumberArray = malloc(sizeof(short) * len);

	// if the last element of the array is 1 it is in use
	for(int i = 0; i < len; i++){
		frameNumberArray[i] = 0;
	}
	return frameNumberArray;
}

void fillMemory(){
	// Getting random number between 2048 and 20480
	srandom(time(NULL))
	int r = (random() % (20480 - 2048)) + 2048;
	for(int i = o; i < r; i ++){
		
	}
}

int main(int argc, char *argv[]){
// Creating array of array of unsigned shorts
// "int" seeingly not needed

	unsigned short physicalMemory = malloc(FRAME_SIZE * TOTAL_FRAMES);
	unsigned short discspace = malloc(PAGETABLE_SIZE);
	//printf("Short is %lu\n", sizeof(short));
	//printf("unsigned short int is %lu\n", sizeof(unsigned short));
	unsigned short* pageTable = createVMTable(PAGETABLE_SIZE);
	unsigned short* tlb = createVMTable(TLB_SIZE);
	return 0;
}
