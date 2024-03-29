// Strother Woog
// 1618221
// CMPS 101
// 7/3/19
// Implementation file for List ADT
// List.c

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
	void* data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	int length;
	int cursor;
} ListObj;

// private List type
typedef ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(void* data){
	Node N = malloc(sizeof(NodeObj));
	// N->data = malloc(sizeof(void));
	N->data = data;
	N->next = N->prev = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0;
	L->cursor = -1;
	return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
	if(pL != NULL && *pL != NULL) { 
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

int isEmpty(List L) {
	if(L == NULL) {
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
	}
	
	return (L->length == 0);
}

int length(List L) {
	if(L == NULL) {
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	
	return (L->length);
}

int index(List L) {
	if(L == NULL) {
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	
	if(!isEmpty(L)) {
		if(L->cursor < L->length  && L->cursor >= 0) 
			return (L->cursor);
		else
			return -1;
	}
	else 
		return -1; 
}

void* front(List L) {
	if(L == NULL) {
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)) {
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}
	
	return L->front->data;
}

void* back(List L) {
	if(L == NULL) {
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)) {
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	
	return(L->back->data);
}

void* get(List L) {
	if(L == NULL) {
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L) || index(L) == -1) {
		printf("List Error: calling get() on an empty List\n");
		exit(1);
	}
	
	int x = 0;
	Node N = L->front;
	while(x < index(L)) {
		x++;
		N = N->next;
	}
	return N->data;
}

// Manipulation procedures ----------------------------------------------------

void clear(List L) {
	if(L == NULL) {
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	
	Node N = L->front;
	while(N != NULL){
		Node M = N;
		N = N->next;
		freeNode(&M);
	}
	
	L->front = L->back = NULL;
	L->length = 0;
	L->cursor = -1;
}

void moveFront(List L) {
	if(L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)) {
		printf("List Error: calling moveFront() on an empty List\n");
		exit(1);
	}
	
	L->cursor = 0;
}

void moveBack(List L) {
	if(L == NULL) {
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)) {
		printf("List Error: calling moveBack() on an empty List\n");
		exit(1);
	}
	
	L->cursor = L->length - 1;

}

void movePrev(List L) {
	if(L == NULL) {
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L) || index(L) == -1) {
		printf("List Error: calling movePrev() on an empty List\n");
		exit(1);
	}
	
	if(index(L) == 0) {
		L->cursor = -1;
	}
	else {
		L->cursor--;
	}
}

void moveNext(List L) {
	if(L == NULL) {
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L) || index(L) == -1) {
		printf("List Error: calling moveNext() on an empty List\n");
		exit(1);
	}
	
	//if(index(L) == length(L) - 1) {
	//	L->cursor = -1;
	//}
	//else {
		L->cursor++;
	//}
}

void prepend(List L, void* data) {
	if(L == NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	
	Node N = newNode(data);
	if(isEmpty(L)) {
		L->front = L->back = N; 
	}
	else {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	L->length = L->length + 1;
	if(index(L) != -1) {
		L->cursor++;
	}
}

void append(List L, void* data) {
	if(L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	
	Node N = newNode(data);
	if(isEmpty(L)) {
		L->front = L->back = N; 
	}
	else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length = L->length + 1;
}

void insertBefore(List L, void* data) {
	if(L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	else if(isEmpty(L) || index(L) == -1) {
		printf("List Error: calling insertBefore() on an empty List\n");
		exit(1);
	}
	else {
		if(L->cursor == 0) {
			prepend(L, data);
		}
		else {
			int x = 0;
			Node N = newNode(data);
			Node M = L->front;
			while(x < L->cursor) {
				x++;
				M = M->next;
			}
			N->prev = M->prev;
			M->prev = N;
			N->next = M;
			N->prev->next = N;
			L->length = L->length + 1;
			L->cursor = L->cursor + 1;
		}
	}
}

void insertAfter(List L, void* data) {
	if(L == NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	else if(isEmpty(L) || L->cursor == -1) {
		printf("List Error: calling insertAfter() on an empty List\n");
		exit(1);
	}
	else {
		if(L->cursor == L->length - 1) {
			append(L, data);
		}
		else {
			int x = 0;
			Node N = newNode(data);
			Node M = L->front;
			while(x < L->cursor) {
				x++;
				M = M->next;
			}
			N->next = M->next;
			M->next = N;
			N->prev = M;
			N->next->prev = N;
			L->length = L->length + 1;
		}
	}
}

void deleteBack(List L) {
	if(L == NULL) {
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)) {
		printf("List Error: calling deleteBack() on an empty1 List\n");
		exit(1);
	}
	
	if(L->length > 1) {
		Node N = L->back;
		L->back = L->back->prev;
		L->back->next = NULL;
		L->length = L->length - 1;
		if(index(L) == length(L)) {
			L->cursor = -1;
		}
		freeNode(&N);
	}
	else {
		clear(L);
	}
	
}

void deleteFront(List L) {
	if(L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)) {
		printf("List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	
	if(L->length > 1) {
		Node N = L->front;
		L->front = L->front->next;
		L->front->prev = NULL;
		L->length = L->length - 1;
		L->cursor = L->cursor - 1;
		freeNode(&N);
	}
	else {
		clear(L);
	}
	
}

void delete(List L) {
	if(L == NULL) {
		printf("List Error: calling delete() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L) || index(L) == -1) {
		printf("List Error: calling delete() on an undefined index\n");
		exit(1);
	}
	
	if(length(L) < 1) {
		deleteFront(L);
	}
	else if(index(L) == 0) {
		deleteFront(L);
	}
	else if(index(L) == L->length - 1) {
		deleteBack(L);
	}
	else {
		Node N = L->front;
		int x = 0;
		while(x < index(L) - 1) {
			N = N->next;
			x++;
		}
		Node M = N->next;
		N->next = N->next->next;
		N->next->prev = N;
		L->length = L->length - 1;
		freeNode(&M);
	}	
}

