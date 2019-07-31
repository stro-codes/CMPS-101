// Strother Woog
// 1618221
// CMPS 101
// 7/27/19
// Sparse Matrix input data to be maipulated for output
// Sparse.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {
	Matrix A = NULL;
	Matrix B = NULL;
	FILE *in, *out;
	int i, a, b, x, y = 0;
	double z = 0.0;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// open files for reading and writing
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	
	// sparse the input file
	while(fscanf(in, "%d", &x) != EOF) {
		if(i == 0) {
			fscanf(in, "%d", &a);
			fscanf(in, "%d", &b);
			printf("%d %d %d\n",x,a,b);
			A = newMatrix(x);
			B = newMatrix(x);
		}
		else if(i > 0) {
			//printf("yeet\n");
			if(i <= a) {
				fscanf(in, "%d", &y);
				fscanf(in, "%lf", &z);
				printf("A %d %d %lf\n",x,y,z);
				changeEntry(A, x, y, z);
			}
			else {
				fscanf(in, "%d", &y);
				fscanf(in, "%lf", &z);
				printf("B %d %d %lf\n",x,y,z);
				changeEntry(B, x, y, z);
			}
		}
		i++;
	}
	
	
	// write to outfile
	fprintf(out, "A has %d non-zero entries: \n", NNZ(A));
	printMatrix(out, A);
	fprintf(out, "\n");

	fprintf(out, "B has %d non-zero entries: \n", NNZ(B));
	printMatrix(out, B);
	fprintf(out, "\n");

	fprintf(out, "(1.5)*A = \n");
	printMatrix(out, scalarMult(1.5,A));
	fprintf(out, "\n");
	
	fprintf(out, "A+B = \n");
	printMatrix(out, sum(A,B));
	fprintf(out, "\n");

	fprintf(out, "A+A = \n");
	printMatrix(out, sum(A,A));
	fprintf(out, "\n");

	fprintf(out, "B-A = \n");
	printMatrix(out, diff(B,A));
	fprintf(out, "\n");
	
	fprintf(out, "A-A = \n");
	printMatrix(out, diff(A,A));
	fprintf(out, "\n");
	
	fprintf(out, "Transpose(A) = \n");
	printMatrix(out, transpose(A));
	fprintf(out, "\n");
	
	fprintf(out, "A*B = \n");
	printMatrix(out, product(A,B));
	fprintf(out, "\n");
	
	fprintf(out, "B*B = \n");
	printMatrix(out, product(B,B));
	fprintf(out, "\n");
	
	// close all inout and output files
	fclose(in);
	fclose(out);
	
	freeMatrix(&A);
	freeMatrix(&B);
	
	return(0);
}