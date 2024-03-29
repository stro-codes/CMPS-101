// Strother Woog
// 1618221
// CMPS 101
// 7/27/19
// Header file for List ADT
// List.h

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);
void freeList(List* pL);

// Access functions -----------------------------------------------------------
int isEmpty(List L);
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* data);
void append(List L, void* data);
void insertBefore(List L, void* data);
void insertAfter(List L, void* data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

#endif