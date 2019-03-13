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

	// page 0 is equal to frame 0 and is set to in use
	frameNumberArray[0] = 0001;

	//page 1 is equal to frame 1 and is set to in use
	frameNumberArray[1] = 257;//0101

	return frameNumberArray;
}

// Should pass the random amount to be passed
void fillMemory(unsigned short *physicalMemory, int startPoint){
	// Getting random number between 2048 and 20480
	srandom(time(NULL));
	int r = (random() % (20480 - 2048)) + 2048;
	for(int i = 0; i < r; i ++){
		// Generating a number between 33 - 126
		unsigned short s = (random() % 126 - 33) + 33;
		if(i <= 1){
			//printf("Random number: %hu\n", s);
		}
		physicalMemory[startPoint] = s;
		startPoint++;
	}
}

unsigned short getFrameNumber(short mask, short value, short shift){
	return ((value & mask)>>shift);
}

unsigned short getOffset(short mask, short value){
	return value & mask;
}

int main(int argc, char *argv[]){
// Creating array of array of unsigned shorts
// Create page table first, then assign memory.
	unsigned short *pageTable = createVMTable(PAGETABLE_SIZE);
        unsigned short *physicalMemory = malloc(FRAME_SIZE * TOTAL_FRAMES);
        unsigned short *discspace = malloc(PAGETABLE_SIZE);

	//unsigned short *tlb = createVMTable(TLB_SIZE);

	fillMemory(physicalMemory,2 * 216);
	printf("Filling memory point %hu\n",*physicalMemory); 
	short value = 1234;
	printf("Getting Address: %hu\n", getFrameNumber(PAGE_MASK, value, BITSHIFT));
	printf("Getting offset: %hu\n", getOffset(OFFSET_MASK, value) );
	//free(tlb);
	free(pageTable);
	free(physicalMemory);
	free(discspace);
	return 0;
}
