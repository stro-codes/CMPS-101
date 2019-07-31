// Strother Woog
// 1618221
// CMPS 101
// 7/27/19
// Test client for the Matrix ADT
// MatrixTest.c

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

   changeEntry(A, 1, 1, 1);
        changeEntry(A, 1, 3, 1);
        changeEntry(B, 1, 1, 1);
        changeEntry(B, 1, 3, 1);
        changeEntry(A, 1, 3, 0);
   //changeEntry(A, 1,1,1); changeEntry(B, 1,2,1);
   //changeEntry(A, 1,2,0); changeEntry(B, 1,1,1); 
                            //changeEntry(B, 1,2,2);
   printf("equals %d \n", equals(A,B));
   
   changeEntry(A, 1, 1, 0);
        makeZero(B);
        changeEntry(A, 10, 10, 10);
        changeEntry(B, 10, 10, 10);
		
	printf("equals %d \n", equals(A,B));
		
   
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1); 
    

   	printf("\n");
    printf("hoot \n");
	//printEntry(stdout, *(Entry*)front(A->arr[0]));
	//printf("\n");
	//printEntry(stdout, E);
	printf("\n");

	
    double d = 2.2;
    printf("%f\n", d);


    printf("A\n");
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

    printf("B:\n");
   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

    printf("Scalar Multiple\n");
   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

    printf("Copy and Equals\n");
   D = copy(A);
   printf("%s\n", equals(A,D)?"true":"false");
   printf("%s\n", equals(A,A)?"true":"false");
   printf("%s\n", equals(D,B)?"true":"false");
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

    printf("Transpose\n");
   E = transpose(A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   printf("Sum\n");
   F = sum(A,B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   Matrix I = scalarMult(-1.0, A);
   printMatrix(stdout, I);
    printf("\n");

    printf("zero\n");
   Matrix J = sum(A, I);
   printMatrix(stdout, J);
   printf("\n");

   printf("Diff\n");
   G = diff(A,B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   printf("zero\n");
   Matrix dif = diff(B,B);
   printMatrix(stdout, dif);
   freeMatrix(&dif);
   printf("\n");
   
   Matrix K = scalarMult(-2.0,B);
       printf("double\n");
    printMatrix(stdout, K);
   printf("\n");

   printf("\n");

   
   printf("Mult\n");
   H = product(A,B);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);



	freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&K);
   freeMatrix(&J);

   return EXIT_SUCCESS;
}
