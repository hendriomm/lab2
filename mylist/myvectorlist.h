#ifndef MY_VECTORLIST
#define MY_VECTORLIST

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef void* DataType;

typedef struct vectorlist{
  DataType *head;
  size_t size;
  size_t index;
  size_t maxSize;
} VectorList;

VectorList* newVectorList ( );


void resizeVectorList ( VectorList** list );

void deleteVectorList ( VectorList** list );

size_t copyVectorList ( VectorList** target, const VectorList** source );

size_t insertHead ( VectorList** list, const DataType data);

size_t insertCursor ( VectorList** list, const DataType data);

size_t deleteCursor ( VectorList** list );

size_t deleteHead(VectorList** list );

size_t deleteEnd(VectorList** list );

void cleanVectorList ( VectorList** list );

bool isEmpty ( VectorList** list );

bool isFull ( VectorList** list );

size_t length(VectorList** list);

int gotoBeginning ( VectorList** list );

size_t gotoEnd ( VectorList** list );

bool gotoNext ( VectorList** list );

bool gotoPrior ( VectorList** list );

DataType getFromCursor ( VectorList** list );

size_t getCursor ( VectorList** list );

void showStructure ( VectorList** list );

size_t updateCursor( VectorList** list, const DataType data );

#endif
