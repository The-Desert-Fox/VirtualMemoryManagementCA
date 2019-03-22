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

unsigned short* createVMTable(unsigned short *physicalMemory, int len ){
	// if the number is even it is not in use
	for(int i = 0; i < len * 2; i++){
		physicalMemory[i] = 0;
	}

	// page 0 is equal to frame 0 and is set to in use
	physicalMemory[0] = 0001;

	//page 1 is equal to frame 1 and is set to in use
	physicalMemory[1] = 257;//0101

	// page 200 is in swap space 1
	physicalMemory[200] = 51203;

	// page 201 is in swap space 2
	physicalMemory[201] = 51460;

	return physicalMemory;
}


// Should pass the random amount to be passed
void fillMemory(unsigned short *physicalMemory, int startPoint){
	// Getting random number between 2048 and 20480
	srandom(time(NULL));
	int r = (random() % (20480 - 2048)) + 2048;
	int pc = 2;
	for(int i = 0; i < r; i++){
		// Marking on page table where memory is stored
		if(startPoint % 256 == 0){
			physicalMemory[pc] = startPoint + 1;
			pc++;
		}
		// Generating a number between 33 - 126
		unsigned short s = (random() % 126 - 33) + 33;
		physicalMemory[startPoint] = s;
		startPoint++;
	}
}

unsigned short getPageNumber(short value, short shift){
	return value >> shift;
}

unsigned short getOffset(short mask, short value){
	return value & mask;
}

// Ints where too small (segmentation fault - core dump)
void printPhysical(unsigned short *physicalMemory, long size ){
	FILE *out_file = fopen("data/physical_memory.txt", "w");
	char inuse;
	for(int i = 0; i < size; i++){
		if(physicalMemory[i] == 0){
			inuse = 'n';
		}else{
			inuse = 'y';
		}
		fprintf(out_file, "Address: %x\tFrame:%d \tContent:%hu \tIn use:%c\n",i, i / 256, physicalMemory[i],inuse);
		//fprintf(stdout, "Address: %ld\tFrame:%ld \tContent:%hu \t\n", i, i /256, physicalMemory[i]);
	}
	fclose(out_file);
}

void printPT(unsigned short *pageTable, long size){
	FILE *out_file = fopen("data/page_table.txt", "w");
	for(long i = 0; i < size; i++){
	fprintf(out_file, "Address: %ld\tPage:%ld \tContent:%hu \t\n",i, i / 256, pageTable[i]);
	}
	fclose(out_file);
}

unsigned short* discGet(){
	unsigned short* disc = malloc(FRAME_SIZE * 4);
	FILE *in_file = fopen("data/onDisc.txt", "r");
	for(int i = 0; i < FRAME_SIZE * 2; i++){
		disc[i] = fgetc(in_file);
	}
	fclose(in_file);
	return disc;
}

int searchTLB(int pn, unsigned short* tlb, int tlbsize){
	for(int i = 0; i < tlbsize * 2; i += 2){
		if(tlb[i] == pn){
			printf("TLB hit. Returning frame number\n");
			return tlb[i + 1] >> 8;
		}
	}
	return 1;
}

int searchPT(int pn, unsigned short* pageTable, int PTsize){
	int point = pageTable[pn] - 1;
	return point >> 8;
}

int main(int argc, char *argv[]){
// Creating array of array of unsigned shorts
// Create page table first, then assign memory.
	int addr;
	unsigned short *physicalMemory = malloc(FRAME_SIZE * TOTAL_FRAMES);
	unsigned short *pageTable = createVMTable(physicalMemory, PAGETABLE_SIZE);
	// Want to store up to 4 frames
        unsigned short *discspace = discGet();
	unsigned short *tlb = malloc(TLB_SIZE * 2); //createTLB(TLB_SIZE);

	printf("Filling memory \n");
	printf("Filling page table\n\n");

	printf("Address from swap space 0 address 5: %d", discspace[5]);
	//printf("Address from swap space 1 address 50: %d", discspace[305]);
	printf("Example of page table layout\n");
	printf("0F01\nTwo most significant bits(0F): Page 15\nSecond least significant bit(0): Which are of swap space it's in(Its not in swap)\nLeast significant bit(1): Is it in use(0: no, 1: yes)\n\n");

	fillMemory(physicalMemory,256 * 4);
	printPhysical(physicalMemory, 256 * 256);
	printPT(pageTable, 256 * 2);
	while(1){
		printf("Enter virtual address:");
		scanf("%x", &addr);

		printf("\nGetting Virtual Page Number\n");
		int pn = addr >> 8;//getPageNumber(addr, 8);
		printf("Virtual Page Number: %d\n\n", pn);

		printf("Getting offset\n");
		int off = getOffset(OFFSET_MASK, addr);
		printf("Offset: %d\n\n", off);

		printf("Consulting TLB\n");
		int tlbRes = searchTLB(pn, tlb, TLB_SIZE);
		if(tlbRes == 1){
			printf("TLB miss\n");
			printf("Searching page table\n");
			tlbRes = searchPT(pn, pageTable, PAGETABLE_SIZE);
			if(tlbRes == -1){
				printf("That page and Frame is not in use\n");
			}else{
				printf("Page number: %d\t Frame Number: %d\n", pn, tlbRes);
				printf("Bitshifting frame number 8 bits to the right then adding offset\n");
				int phyAddr = (tlbRes << 8) + off;
				printf("Physical address: %x\t Content at address: %d\n", phyAddr, physicalMemory[phyAddr]);
				printf("Adding addresses to TLB\n");
				tlb[0] = pn;
				tlb[1] = tlbRes;
			}
		}else{
			printf("Bitshifting frame number 8 bits to the right then adding offset\n");
			int phyAddr = (tlbRes << 8) + off;
			printf("Physical address: %x\t Content at address: %d\n", phyAddr, physicalMemory[phyAddr]);
		}
	
	}

	free(tlb);
	//free(pageTable);
	free(physicalMemory);
	free(discspace);
	return 0;
}
