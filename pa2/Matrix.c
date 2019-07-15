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
};

typedef MatrixObj* Matrix;

// contructor - destructor

Entry newEntry(double data, int column) {
    Entry E = malloc(sizeof(EntryObj));
    E->data = data;
    E->column = column;
    return E;
}

void freeEntry(Entry* pE) {
    if(pG != NULL && *pG != NULL) {
        makeNull(*pG);
        free(*pG);
        *pG = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->n = n;
    for(int i = 0; i < n, i++) {
        List[i] = newList();
    }
    return M
}

void freeMatrix() {
    if(pM != NULL && *pM != NULL) {

    }
}

// access function

int size(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling size() on NULL Matrix reference\n");
        exit(1);
    }

    return E->data;
}

int NNZ(Entry E) {
    if(M == NULL) {
        printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(1);
    }

    int result = 0;
    for(int i = 0; i < size(E); i++) {
        result += Length(E->arr[i]);
    }
    return result;
}

int equals(Matrix A, Matrix B) {

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
        if(isEmpty(L)) {
            if(x != 0.0)
                prepend(l, E);
        }
        else {
            moveFront(L);
            while (index(L) != -1) {
                Entry F = get(L);
                if(E->column == F->column) {
                    if(E->data == 0.0)
                        delete(L);
                    else {
                        F->data = E->data;
                    }
                    break;
                }
            }
            if(length(L) != 0) {
                Entry F = back(L);
                if(E->column > F->column) {
                    if(E->data != 0)
                        append(L, E);
                }
            }
        }
    }
}

// arithmetic operations

