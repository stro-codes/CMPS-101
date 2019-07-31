// Strother Woog
// 1618221
// CMPS 101
// 7/27/19
// Test client for the List ADT
// ListTest.c

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   
   int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
   int i;

   // initialize Lists A and B
   for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
   }

   moveFront(A);
   delete(A);
   
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   
   freeList(&A);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
A equals C is true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
20 19 18 17 16 -2 15 14 13 12 11 9 8 7 6 -1 5 4 3 2 1
21
0
*/