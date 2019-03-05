#include <stdio.h>
#include "vmFunctions.h"

int main(int argc, char *argv[]){
// Creating array of array of unsigned shorts
// "int" seeingly not needed
	unsigned short physicalMemory[65536];
	
	printf("Short is %lu\n", sizeof(short));
	printf("unsigned short int is %lu\n", sizeof(unsigned short));

	return 0;
}
