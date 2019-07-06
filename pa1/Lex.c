// Strother Woog
// 1618221
// CMPS 101
// 7/3/19
// Runs InsertSort on a List of indicies based on a String Array
// Lex.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 256

int main(int argc, char* argv[]){
   
	int n = 0;
	int count = 0;
	FILE *in, *in2, *out;
	char line[MAX_LEN];

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	in2 = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	
	// check if files are available
	if(in == NULL || in2 == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	// grab number of lines from input file
	while(fgets(line, sizeof(line), in2) != NULL) {
		count++;
	}
	
	// initialize array of strings for the lines from input file
	char tokenlist[count][MAX_LEN];
	
	// store each line from input file in array
	while(fgets(line, sizeof(line), in) != NULL) {
		strcpy(tokenlist[n], line);
		n++;
	}
	
	// insert sort algorithm
	List L = newList();
	prepend(L, 0);
	moveFront(L);
	for(int j = 1; j < count; j++) {
		strcpy(line, tokenlist[j]);
		moveFront(L);
		while(index(L) < j - 1) {
			moveNext(L);
		}
		while(index(L) > -1 && strcmp(tokenlist[get(L)], line) > 0) {
			movePrev(L);
		}
		if(index(L) == -1) {
			prepend(L, j);
		}	
		else {
			insertAfter(L, j);
		}
	}
	
	// print list to output file
	moveFront(L);
	for(int i = 0; i < count; i++){
		fprintf(out, "%s", tokenlist[get(L)]);
		if(i != count - 1)
			moveNext(L);
	}
	
	// free heap memory
	freeList(&L);
	
	// close all input and output files
	fclose(in);
	fclose(in2);
	fclose(out);
   
	return(0);
}
