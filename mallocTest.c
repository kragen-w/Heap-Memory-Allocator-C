// This is the main with the testing code for DuMalloc/DuFree

#include <stdio.h>  // printf
#include <stdlib.h>  // exit




// Load in the dumalloc interface
// Will need to be compiled with the dumalloc code as well
//   but for this lab we use a makefile to create a library
//   and link with that.  See the makefile.
#include "dumalloc.h"

void shortTest() {
	printf("\nduMalloc a1\n");
	char* a1 = (char*)duMalloc(128);
	if (a1 == NULL) {
		printf("Call to DuMalloc failed\n");
		exit(1);
	}
	duMemoryDump();

	// Test to see that memory access works through the pointer
	a1[0] = 'D';
	a1[1] = 'e';
	a1[2] = 'n';
	a1[3] = 'v';
	a1[4] = 'e';
	a1[5] = 'r';
	a1[6] = '\0';
	printf("\nMemory access is: %s\n", a1);
	printf("\nduFree a1\n");
	duFree(a1);
	duMemoryDump();
}

void longTest() {
	printf("\nduMalloc a1\n");
	char* a1 = (char*)duMalloc(128);
	if (a1 == NULL) {
		printf("Call to DuMalloc failed\n");
		exit(1);
	}
	duMemoryDump();




	// Should round up to 32 bytes since it needs to be multiple of 8
	printf("\nduMalloc a2\n");
	char* a2 = (char*)duMalloc(30);
	if (a2 == NULL) {
		printf("Call to DuMalloc failed\n");
		exit(1);
	}

	duMemoryDump();

	printf("\nduMalloc a3\n");
	char* a3 = (char*)duMalloc(80);
	if (a3 == NULL) {
		printf("Call to DuMalloc failed\n");
		exit(1);
	}
	duMemoryDump();



	printf("\nduMalloc a4\n");
	char* a4 = (char*)duMalloc(120);
	if (a4 == NULL) {
		printf("Call to DuMalloc failed\n");
		exit(1);
	}


	duMemoryDump();



	printf("\nduFree a2\n");



	duFree(a2);
	duMemoryDump();

	// This should not coalese with the other free block
	printf("\nduFree a3\n");
	duFree(a3);
	duMemoryDump();

	// First fit will skip the 32 block and find the 80 block
	printf("\nduMalloc a5\n");
	char* a5 = (char*)duMalloc(40);
	if (a5 == NULL) {
		printf("Call to DuMalloc failed\n");
		exit(1);
	}
	duMemoryDump();

	// Create a new freeList head test
	printf("\nduFree a1\n");
	duFree(a1);
	duMemoryDump();

	// Test out of memory
	printf("\nduMalloc a6\n");
	char* a6 = (char*)duMalloc(800);
	if (a6 == NULL) {
		printf("Call to DuMalloc failed\n");
		exit(1);
	}
	duMemoryDump();

}

int main(int argc, char* argv[]) {

	// Must be first call in the program to get DuMalloc going
	printf("\nduInitMalloc\n");
	duInitMalloc();
	duMemoryDump();

	// shortTest();
	// OR
	longTest();
	printf("\nhello bro\n");
}
