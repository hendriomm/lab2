#include "mylinkedlist.h"

LinkedList* newLinkedList(){
  LinkedList* new = (LinkedList*) malloc(sizeof(LinkedList));
  new->head = NULL;
  new->cursor = new->head;
  new->size = 0;
  new->index = -1;
}

void deleteLinkedList ( LinkedList** list ){
  cleanLinkedList(list);
  free(*list);
}
void cleanLinkedList ( LinkedList** list ){
  while(deleteHead(list) != 0);
}

size_t copyLinkedList ( LinkedList** target, const LinkedList** source) {
  Node *src = (*source)->head;
  deleteLinkedList(target);
  while(src != NULL){
    insertCursor(target, src->data);
    src = src->next;
  }
  return (*target)->size;
}

Node* createNode(void* data){
  Node* n = (Node*) malloc(sizeof(Node));
  n->data = data;
  n->prev = NULL;
  n->next = NULL;
  return n;
}

//display the list
void showStructure(LinkedList** list) {
   Node *ptr = (*list)->head;
   printf("\n[ ");

   //start from the beginning
   while(ptr != NULL) {
      printf("(%s)",(char*)ptr->data);
      if ( ptr == (*list)->cursor ) printf("*");
      printf(" ");
      ptr = ptr->next;
   }

   printf(" ] ");
   printf("size: %lu index: %ld", (*list)->size, (*list)->index);
}

//insere nó na frente do cursor
size_t insertCursor(LinkedList** list, const DataType data) {
   Node *link = createNode(data);

   if((*list)->size == 0){
     (*list)->head = link;
   }
   else {
     Node* cursor = (*list)->cursor;
     Node* next = cursor->next;

     link->prev = cursor;
     link->next = cursor->next;

     cursor->next = link;
     if(next != NULL)
      next->prev = link;
   }

   (*list)->cursor = link;
   (*list)->size++;
   (*list)->index++;
   return (*list)->size;
}

//delete cursor item
size_t deleteCursor(LinkedList** list) {
  if ( (list == NULL) || isEmpty(list) )
     return 0;

  Node* tobeDeleted = (*list)->cursor;

  /* Se o nó a ser deletado for o primeiro */
  if ( (*list)->head == tobeDeleted ){
    (*list)->head = tobeDeleted->next;
    (*list)->cursor = (*list)->head;
  }

  /* Se o nó a ser deletado não for o último */
  if ( tobeDeleted->next != NULL ){
    tobeDeleted->next->prev = tobeDeleted->prev;
    (*list)->cursor = tobeDeleted->next;
  } else {
    (*list)->cursor = tobeDeleted->prev;
    (*list)->index--;
  }

  /* Se o nó a ser deletado não for o primeiro*/
  if ( tobeDeleted->prev != NULL )
    tobeDeleted->prev->next = tobeDeleted->next;

  free(tobeDeleted->data);
  free(tobeDeleted);
  (*list)->size--;

  return (*list)->size;
}

size_t deleteHead(LinkedList** list){
  Node* head = (*list)->head;
  if ((*list)->size == 0)
    return 0;
  if ( (*list)->size == 1 ) {
    // if the size is 1 set the head to NULL since there are no other nodes
    (*list)->head = NULL;
    (*list)->cursor = NULL;
  } else {
    Node *next = head->next;
    if ( (*list)->cursor == (*list)->head){
      (*list)->cursor = next;
    }

    // update the head
    (*list)->head = next;

    // update the pointers
    next->prev = NULL;
  }

  // free the data and the node
  free(head->data);
  free(head);

  (*list)->size--;

  return (*list)->size;
}

size_t deleteEnd(LinkedList** list){
  gotoEnd(list);
  return deleteCursor(list);
}

//is list empty
bool isEmpty ( LinkedList** list ) {
   return (*list)->size == 0;
}

//is list full
bool isFull ( LinkedList** list ) {
   return false;
}

size_t length(LinkedList** list) {
   return (*list)->size;
}

int gotoBeginning ( LinkedList** list ){
  if ( (*list)->size != 0 ) {
    (*list)->cursor = (*list)->head;
    (*list)->index = 0;
    return 0;
  }
  return -1;
}

int gotoEnd ( LinkedList** list){
  if((*list)->cursor->next == NULL)
    return -1;
  while((*list)->cursor->next != NULL)
    (*list)->cursor = (*list)->cursor->next;

  (*list)->index = ((*list)->size - 1);
  return ((*list)->size - 1);
}

bool gotoNext ( LinkedList** list ){
  if((*list)->cursor->next != NULL){
    (*list)->cursor = (*list)->cursor->next;
    (*list)->index++;
    return true;
  }
  return false;
}

bool gotoPrior ( LinkedList** list ){
  if((*list)->cursor->prev != NULL){
    (*list)->cursor = (*list)->cursor->prev;
    (*list)->index--;
    return true;
  }
  return false;
}

DataType getFromCursor ( LinkedList** list ){
  return (*list)->cursor->data;
}

size_t getCursor ( LinkedList** list ){
  return (*list)->index;
}

size_t updateCursor( LinkedList** list, const DataType data ){
  (*list)->cursor->data = data;
  return (*list)->index;
}
