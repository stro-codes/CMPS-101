//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
#include"List.h"
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;
   
   //Entry E = newEntry(1,3.4);

   printf("give a \n");

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0); 
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1); 

   	printf("\n");
    printf("hoot to this \n");
	//printEntry(stdout, *(Entry*)front(A->arr[0]));
	//printf("\n");
	//printEntry(stdout, E);
	printf("\n");

	
    double d = 2.2;
    printf("%f\n", d);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = copy(A);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = transpose(A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");


   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);

   return EXIT_SUCCESS;
}
