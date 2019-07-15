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
}

void freeMatrix() {

}

// access function

int size(Entry E) {
    return E->data;
}

int NNZ(Entry E) {
    int result = 0;
    for(int i = 0; i < size(E); i++) {
        result += Length(E->arr[i]);
    }
    return result;
}
