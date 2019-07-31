// Strother Woog   
// 1618221
// CMPS 101
// 7/27/19
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
        M->arr[i] = newList();
    }
    return M;
}

void freeMatrix(Matrix* pM) {
    if(pM != NULL && *pM != NULL) {
        makeZero(*pM);
		for(int i = 0; i < size(*pM); i++) {
			List L = (*pM)->arr[i];
			freeList(&L);
		
		} 
		free((*pM)->arr);
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
	
	fprintf(out, "(%d,%.1f) ", E->column, E->data);
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
    if(A == NULL || B == NULL) {
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(1);
    }

    int foo = 0;
    
    // A & B are the same Matrix in Memory
    if(A == B) {
        return 1;
    }

    if(size(A) == size(B)) {
		
		if(NNZ(A) != NNZ(B))
			return 0;

        for(int i = 0; i < size(A); i++) {
            List L = A->arr[i];
            List N = B->arr[i];
			
			if(length(L) != length(N))
				return 0;

            if(!isEmpty(L) && !isEmpty(N)) {
                moveFront(L);
                moveFront(N);
                while(index(L) >= 0 && index(N) >= 0) {

                    Entry E = get(L);
                    Entry F = get(N);
                    if(E->column != F->column)
                        return 0;
                    else {
                        if(E->data != F->data)
                            return 0;
                        else 
                            foo = 1;
                    }
                         
                    moveNext(L);
                    moveNext(N);
                }   
            }
            else if(isEmpty(L) && isEmpty(N))
                foo = 1;
			else
				return 0;

        }
    }
    else {
        return 0;
	}
		
	return foo;
}

// manipulation

void makeZero(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(1);
    }

    for(int i = 0; i < size(M); i++) {
        List L = M->arr[i];
        if(!isEmpty(L))
            moveFront(L);
        while(length(L) > 0) {
			moveFront(L);
            Entry E = get(L);
            freeEntry(&E);
			delete(L);
        }
		clear(L);
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
		// append if row is empty
        if(isEmpty(L)) {
            if(x != 0.0) {
                prepend(L, newEntry(j, x));
            }
        }
		// if row has items 
        else {
            moveFront(L);
            while(index(L) >= 0) {
                Entry F = get(L);
				// if the columns match
                if(j == F->column) {
                    // delete column with zero entry
                    if(x == 0.0) {
						freeEntry(&F);
						delete(L);
					}
					// replace rolumn with different entry
                    else
                        F->data = x;
                    break;
                }
				// insert new column between row with new entry
                else if(j < F->column) {
                    if(x != 0.0)
                        insertBefore(L, newEntry(j, x));
                    break;
                }
                else {
                    moveNext(L);
                }
            }
            if(length(L) != 0) {
                Entry F = back(L);
				// prepend new column at the end of row with new entry
                if(j > F->column) {
                    if(x != 0.0)
                        append(L, newEntry(j, x));
                }
            }
        }
    }
}

// matrix arithmetic operations

Matrix copy(Matrix A) {
    if(A == NULL) {
        printf("Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(1);
    }

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
    if(A == NULL) {
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(1);
    }

    Matrix result = newMatrix(size(A));
    for(int i = 0; i < size(A); i++) {
        List L = A->arr[i];
        if(!isEmpty(L))
            moveFront(L);
        while(index(L) >= 0) {
            Entry E = get(L);
            append(result->arr[E->column - 1], newEntry(i + 1, E->data));
            moveNext(L);
        }
    }
    return result;
}

Matrix scalarMult(double x, Matrix A) {
    if(A == NULL) {
        printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(1);
    }

    Matrix result = newMatrix(size(A));
    for(int i = 0; i < size(A); i++){
        List L = A->arr[i];
        if(!isEmpty(L))
            moveFront(L);
        while(index(L) >= 0) {
            Entry E = get(L);
            append(result->arr[i], newEntry(E->column, E->data * x));
            moveNext(L);
        }
    }
    return result;
}

Matrix sum(Matrix A, Matrix B) {
    if(A == NULL || B == NULL) {
        printf("Matrix Error: calling sum() on NULL Matrix refernce");
        exit(1);
    }

    // Check for the same size Matrix
    if(size(A) != size(B)) {
        printf("Matrix Error: calling sum() on mismatched Matrix sizes");
        exit(1);
    }
	else if(equals(A, B)) {
		return scalarMult(2.0, A);
	}
    // If A != B, Then A + B
    else {
        // Make a copy of Matrix A to modify
		Matrix result = copy(A);

        // Modify copy to be Matrix Result
        for(int i = 0; i < size(A); i++) {
            List L = B->arr[i];
            List N = result->arr[i];
            // Make sure either of the Rows are empty to start at their correct Index
            if(!isEmpty(L))
                moveFront(L);
            if(!isEmpty(N))
                moveFront(N);
            for(int j = 0; j < length(L); j++) {
                Entry E = get(L);
                if(index(N) >= 0) {
                    Entry F = get(N);
                    if(E->column == F->column) {
                        F->data = F->data + E->data;
                        if(F->data == 0.0) {
                            freeEntry(&F);
							delete(N);
                            moveNext(L);
                            if(!isEmpty(N) && index(N) == -1) 
                                moveFront(N);
                        }
                        else {
                            moveNext(L);
                            moveNext(N);
                        }
                    }
                    else if(E->column < F->column) {
                        insertBefore(N, newEntry(E->column, E->data));
                        moveNext(L);
                    }
                    else {
                        moveNext(N);
                        j--;
                    }
                }
                else {
                    append(N, newEntry(E->column, E->data));
                    moveNext(L);
                }
            }
            // Matrix Row Addition Complete  
        }
        return result;  
    }
}
// returns a new Matrix that is the sum of Matrix A & B
// pre: size(A)== size(B)

Matrix diff(Matrix A, Matrix B) {
    if(A == NULL || B == NULL) {
        printf("Matrix Error: calling sum() on NULL Matrix refernce");
        exit(1);
    }

    // Check for the same size Matrix
    if(size(A) != size(B)) {
        printf("Matrix Error: calling sum() on mismatched Matrix sizes");
        exit(1);
    }
    // If A != B, Then A - B
    else if(equals(A, B)) {
        return newMatrix(size(A));
    }
    else {
        // Make a copy of Matrix A to modify
        Matrix result = copy(A);
        // Modify copy to be Matrix Result
        for(int i = 0; i < size(A); i++) {
            List L = B->arr[i];
            List N = result->arr[i];
            // Make sure either of the Rows are empty to start at their correct Index
            if(!isEmpty(L))
                moveFront(L);
            if(!isEmpty(N))
                moveFront(N);
            for(int j = 0; j < length(L); j++) {
                Entry E = get(L);
                if(index(N) >= 0) {
                    Entry F = get(N);
                    if(E->column == F->column) {
                        F->data = F->data - E->data;
                        if(F->data == 0.0) {
                            freeEntry(&F);
							delete(N);
                            moveNext(L);
                            if(!isEmpty(N) && index(N) == -1) 
                                moveFront(N);
                        }
                        else {
                            moveNext(L);
                            moveNext(N);
                        }
                    }
                    else if(E->column < F->column) {
                        insertBefore(N, newEntry(E->column, E->data * -1.0));
                        moveNext(L);
                    }
                    else {
                        moveNext(N);
                        j--;
                    }
                }
                else {
                    append(N, newEntry(E->column, E->data * -1.0));
                    moveNext(L);
                }
            }
            // Matrix Row Substraction Complete  
        }
        return result;  
    }
}
// returns a new Matrix that is the difference of Matrix A & B
// pre: size(A)== size(B)

double vectorDot(List L, List R) {
	double result = 0.0;
	if(L == NULL || R == NULL)
		return 0.0;
	if(isEmpty(L) || isEmpty(R)) {
		return 0.0;
	}
	else {
		moveFront(L);
		moveFront(R);
		while(index(L) >= 0 && index(R) >= 0) {
			Entry E = get(L);
			Entry F = get(R);
			if(E->column == F->column) {
				result = result + (E->data * F->data);
				moveNext(L);
				moveNext(R);
			}
			else if(E->column < F->column) {
				moveNext(L);
			}
			else {
				moveNext(R);
			}
		}
	}
	return result;
}
// returns the vector dot product of Matrix rows

Matrix product(Matrix A, Matrix B) {
	if(A == NULL || B == NULL) {
        printf("Matrix Error: calling product() on NULL Matrix refernce");
        exit(1);
    }

    // Check for the same size Matrix
    if(size(A) != size(B)) {
        printf("Matrix Error: calling product() on mismatched Matrix sizes");
        exit(1);
    }
	else {
		Matrix result = newMatrix(size(A));
		Matrix tran = transpose(B);
		for(int i = 0; i < size(A); i++) {
			List L = A->arr[i];
			if(!isEmpty(L)) {
				for(int j = 0; j < size(A); j++) {
					List R = tran->arr[j];
					if(!isEmpty(R)) {	
						double vd = vectorDot(L, R);
						if(vd != 0.0) 
							append(result->arr[i], newEntry(j + 1, vd));	
					}
				}
			}
		}
		freeMatrix(&tran);
		return result;
	}
}
//  returns a new Matrix that is the the product of Matrix A & B, using the Transpose of Matrix B

// other functions

void printMatrix(FILE* out, Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling printMatrix() on NULL Matrix refernce");
        exit(1);
    }

    for(int i = 0; i < size(M); i++) {
        List L = M->arr[i];

        if(!isEmpty(L)) {
            moveFront(L);
            fprintf(out, "%d: ", (i + 1));    

            while(index(L) >= 0) {
                printEntry(out, get(L));
                moveNext(L);
            }

            fprintf(out, "\n");
        }
    }
}
// prints out an adjacanecy list representation of a Matrix