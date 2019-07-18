// Strother Woog   
// 1618221
// CMPS 101
// 7/22/19
// Matrix ADT for Non-Zero Entries
// Matrix.c

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"

// structs

typedef struct EntryObj {
    double data;
    int column;
} EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj {
    int n;
    List* arr;
} MatrixObj;

typedef MatrixObj* Matrix;

// contructor - destructor

Entry newEntry(int column, double data) {
    Entry E = malloc(sizeof(EntryObj));
    E->data = data;
    E->column = column;
    return E;
}

void freeEntry(Entry* pE) {
    if(pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->arr = calloc(n, sizeof(List));
    M->n = n;
    for(int i = 0; i < n; i++) {
		List L = newList();
        M->arr[i] = L;
    }
    return M;
}

void freeMatrix(Matrix* pM) {
    if(pM != NULL && *pM != NULL) {
        makeZero(*pM);
        free(*pM);
        *pM = NULL;
    }
}

// access function

void printEntry(FILE* out, Entry E) {
	if(E == NULL) {
        printf("Entry Error: calling printEntry() on NULL Entry refernce");
        exit(1);
    }
	
	fprintf(out, "(%d,%f) ", E->column, E->data);
}

int size(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling size() on NULL Matrix reference\n");
        exit(1);
    }

    return M->n;
}

int NNZ(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(1);
    }

    int result = 0;
    for(int i = 0; i < size(M); i++) {
        result += length(M->arr[i]);
    }
    return result;
}

int equals(Matrix A, Matrix B) {
    int bool = 0;
    if(size(A) == size(B) && NNZ(A) == NNZ(B)) {
        for(int i = 0; i < size(A); i++) {
            if( (A) == (B)) {
                bool = 1;
            }
            else {
                bool = 0;
                break;
            }
        }
    }


    return bool;
}

// manipulation

void makeZero(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(1);
    }

    for(int i = 0; i < size(M); i++) {
        clear(M->arr[i]);
    } 
}

void changeEntry(Matrix M, int i, int j, double x) {
    if(M == NULL) {
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(1);
    }
    if( !( ( 1 <= i && i <= size(M) ) && ( 1 <= j && j <= size(M) ) ) ) {
        printf("Matrix Error: calling changeEntry() on invalid index");
        exit(1);
    }
    else {
        List L = M->arr[i - 1];
        Entry E = newEntry(j, x);
		// append if row is empty
        if(isEmpty(L)) {
            if(x != 0.0) {
                prepend(L, E);
				printEntry(stdout, front(L));
            }
        }
		//printEntry(stdout, E);
		// if row has items 
        else {
            moveFront(L);
            while(index(L) >= 0) {
                Entry F = get(L);
				// if the columns match
                if(E->column == F->column) {
                    // delete column with zero entry
                    if(E->data == 0.0)
                        delete(L);
					// replace rolumn with different entry
                    else
                        F->data = E->data;
                    break;
                }
				// insert new column between row with new entry
                else if(E->column < F->column) {
                    if(E->data != 0.0)
                        insertBefore(L, E);
                    break;
                }
                else {
                    moveNext(L);
                }
            }
            if(length(L) != 0) {
                Entry F = back(L);
				// prepend new column at the end of row with new entry
                if(E->column > F->column) {
                    if(E->data != 0.0)
                        append(L, E);
                }
            }
        }
    }
}

// matrix arithmetic operations

Matrix copy(Matrix A) {
    Matrix result = newMatrix(size(A));
    for(int i = 0; i < size(A); i++) {
        List L = A->arr[i];
        if(!isEmpty(L))
            moveFront(L);
        while(index(L) >= 0) {
            Entry E = get(L);
            Entry F = newEntry(E->column, E->data);
            append(result->arr[i], F);
            moveNext(L);
        }
    }
    return result;
}

Matrix transpose(Matrix A) {
    Matrix result = newMatrix(size(A));
    for(int i = 0; i < size(A); i++) {
        List L = A->arr[i];
        if(!isEmpty(L))
            moveFront(L);
        while(index(L) >= 0) {
            Entry E = get(L);
            Entry F = newEntry(i + 1, E->data);
            append(result->arr[E->column - 1], F);
            moveNext(L);
        }
    }
    return result;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix result = newMatrix(size(A));
    for(int i = 0; i < size(A); i++){
        List L = A->arr[i];
        if(!isEmpty(L))
            moveFront(L);
        while(index(L) >= 0) {
            Entry E = get(L);
            Entry F = newEntry(E->column, E->data * 1.5);
            append(result->arr[i], F);
            moveNext(L);
        }
        
    }
    return result;
}

// other

void printMatrix(FILE* out, Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling printMatrix() on NULL Matrix refernce");
        exit(1);
    }

    for(int i = 0; i < size(M) - 1; i++) {
        List L = M->arr[i];

        if(isEmpty(L)) {
            break;
        }
        else {
            moveFront(L);
            fprintf(out, "%d: ", (i + 1));    
        }

        while(index(L) >= 0) {
			printEntry(stdout, get(L));
			moveNext(L);
        }

        fprintf(out, "\n");
    }
}
