#include "myvectorlist.h"

const size_t capacityFactor = 2;
const bool isResizeable = true;

VectorList* newVectorList ( ) {
  VectorList* new = (VectorList*) malloc(sizeof(VectorList));
  new->head = malloc ( capacityFactor * sizeof(void*) );
  new->size = 0;
  new->index = 0;
  new->maxSize = capacityFactor;
  return new;
}

void resizeVectorList ( VectorList** list ){
  DataType *newHead = realloc ( (*list)->head, capacityFactor*sizeof(void*)*(*list)->maxSize );
  if ( newHead != NULL){
    (*list)->head = newHead;
    (*list)->maxSize = capacityFactor*(*list)->maxSize;
  } else {
    exit(-1);
  }
}

void deleteVectorList ( VectorList** list ){
  cleanVectorList(list);
  free ( (*list)->head );
  free ( (*list) );
}

size_t copyVectorList ( VectorList** target, const VectorList** source ){
  int i = 0;
  while ( i < (*source)->size ){
    insertCursor(target, (*source)->head[i++]);
  }
  return (*target)->size;
}

size_t insertHead ( VectorList** list, const DataType data){
  if ( ((*list)->size == (*list)->maxSize) && isResizeable )
    resizeVectorList(list);
  size_t i;
  for (i = (*list)->size; i > 0 ; --i){
    (*list)->head[i] = (*list)->head[i-1];
  }
  (*list)->head[0] = data;
  (*list)->size++;
  return (*list)->size;
}

size_t insertCursor ( VectorList** list, const DataType data){
  if ( ((*list)->size == (*list)->maxSize) && isResizeable )
    resizeVectorList(list);
  if ( (*list)->size == 0)
    return insertHead(list, data);
  size_t i;
  (*list)->index++;
  for (i = (*list)->size; i > (*list)->index ; --i){
    (*list)->head[i] = (*list)->head[i-1];
  }
  (*list)->head[(*list)->index] = data;
  (*list)->size++;
  //(*list)->head[(*list)->index] = data;
  return (*list)->size;
}

size_t deleteCursor ( VectorList** list ){
  int i;
  for (i = (*list)->index; i < (*list)->size - 1; i++) {
    (*list)->head[i] = (*list)->head[i + 1];
    (*list)->head[i + 1] = NULL;
  }
  (*list)->size--;
  if ( ( (*list)->index == (*list)->size ) && ( (*list)->size != 0 ) )
    (*list)->index--;
  return (*list)->size;
}

size_t deleteHead(VectorList** list){
  int i;
  for (i = 0; i < (*list)->size - 1; i++) {
    (*list)->head[i] = (*list)->head[i + 1];
    (*list)->head[i + 1] = NULL;
  }
  (*list)->size--;
  return (*list)->size;
}


size_t deleteEnd(VectorList** list){
  gotoEnd(list);
  return deleteCursor(list);
}

void cleanVectorList ( VectorList** list ){
  while(!isEmpty(list)){
    deleteEnd(list);
  }
}

bool isEmpty ( VectorList** list ){
  return (*list)->size == 0;
}

bool isFull ( VectorList** list ){
  return (*list)->size == (*list)->maxSize;
}

size_t length(VectorList** list){
  return (*list)->size;
}

int gotoBeginning ( VectorList** list ){
  if ( (*list)->size != 0){
    (*list)->index = 0;
    return 0;
  }
  return -1;
}

size_t gotoEnd ( VectorList** list ){
  (*list)->index = (*list)->size-1;
  return (*list)->index;
}

bool gotoNext ( VectorList** list ){
  if ( (*list)->index == (*list)->size - 1)
    return false;
  (*list)->index++;
  return true;
}

bool gotoPrior ( VectorList** list ){
  if ( (*list)->index == 0 )
    return false;
  (*list)->index--;

  return true;
}

DataType getFromCursor ( VectorList** list ){
  return (*list)->head[(*list)->index];
}

size_t getCursor ( VectorList** list ){
  return (*list)->index;
}

void showStructure ( VectorList** list ){
  size_t i = 0;
  size_t size = (*list)->size;
  DataType* data = (*list)->head;
  printf("\n[ ");

  //start from the beginning
  while( i < size ) {
     printf("(%s)",(char*) data[i]);
     if ( i == (*list)->index ) printf("*");
     printf(" ");
     i++;
  }

  printf(" ] ");
  printf("size: %lu index: %ld maxSize: %lu", (*list)->size, (*list)->index, (*list)->maxSize );
}

size_t updateCursor( VectorList** list, const DataType data ){
  (*list)->head[(*list)->index] = data;
}
