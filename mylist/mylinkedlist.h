#ifndef MY_LINKEDLIST
#define MY_LINKEDLIST
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef void* DataType;
struct node;
typedef struct node Node;
typedef struct node{
   DataType data;
   Node *next;
   Node *prev;
} Node;

typedef struct linkedlist{
  Node *head;
  Node *cursor;
  size_t size;
  size_t index;
} LinkedList;



/*
 * Construtor
 * Cria uma lista em branco. Aloca memória suficiente para uma lista contendo
 * maxNumber itens de dados.
 */

LinkedList* newLinkedList ();

/*
 * Destrutor
 * Libera a memória alocada para armazenar a lista.
 * (list deve existir e não pode ser nulo)
 */

void deleteLinkedList ( LinkedList** list );

/*
 * Operação de cópia
 * Ajusta a lista target para conter os mesmos elementos do objeto other
 * recebido como parâmetro. Se target continha algum dado, este é perdido. Se ocorrer um erro, -1
 * deve ser retornado, ou um número de itens que foram copiados.
 * (target e source devem existir e não podem ser nulos.)
 */

size_t copyLinkedList ( LinkedList** target, const LinkedList** source );

/*
 * Insere newDataItem na lista
 * Se a lista não estiver vazia, insere após a posição atual do cursor.
 * Caso contrário, insere newDataItem na primeria posição da lista. Em ambos os casos, atualiza o
 * cursor para a posição de newDataItem e retorna esta posição
 * (list não pode ser nulo)
 */

Node* createNode(void* data);
size_t insertCursor(LinkedList** list, const DataType data);

/*
 * Remove o item de dado marcado pelo cursor
 * Se o resultado da operação for uma lista vazia, o
 * cursor deve ser colocado no início da lista. Caso contrário, atualiza a posição do cursor para a
 * posição seguinte à posição atual. Se a posição atual for a última, mantém a posição no novo último
 * item da lista. Esta operação preserva a ordem dos demais elementos da lista. Retorna a nova posição
 * do cursor.
 * (list não pode ser nulo)
 */

size_t deleteCursor(LinkedList** list);
size_t deleteHead(LinkedList** list);
size_t deleteEnd(LinkedList** list);

/*
 * Substitui o item de dado marcado pelo cursor por newDataItem
 * O cursor permanece na mesma posição e este valor é retornado.
 * (list não pode ser nulo)
 */

int replace ( const LinkedList list, const DataType newDataItem );

/*
 * Remove todos os itens de dados da lista.
 * (list não pode ser nulo)
 */

void cleanLinkedList ( LinkedList** list );

/*
 * Returna true se a lista está vazia, caso contrário, retorna false .
 * (list não pode ser nulo)
 */

bool isEmpty ( LinkedList** list );

/*
 * Returna true se a lista está cheia, caso contrário, retorna false .
 * (list não pode ser nulo)
 */

bool isFull ( LinkedList** list );

/*
 * Se a lista não estiver vazia, move o cursor para o primeiro item de dado e retorna o valor 0. Se
 * estiver vazia retorna -1.
 * (list não pode ser nulo)
 */

size_t length(LinkedList** list);
int gotoBeginning ( LinkedList** list );

/*
 * Se a lista não estiver vazia, move o cursor para o último item de dado e retorna este índice. Se
 * estiver vazia retorna -1.
 * (list não pode ser nulo)
 */

int gotoEnd ( LinkedList** list );

/*
 * Se o cursor não está no fim da lista, move-o para o próximo item e retorna true . Caso contrário,
 * retorna false .
 * (list não pode ser nulo)
 */

bool gotoNext ( LinkedList** list );

/*
 * Se o cursor não está no início da lista, move-o para o item anterior e retorna true . Caso contrário,
 * retorna false.
 * (list não pode ser nulo)
 */

bool gotoPrior ( LinkedList** list );

/*
 * Retorna o valor do item de dado apontado atualmente pelo cursor.
 * (list não pode ser nulo)
 */

DataType getFromCursor ( LinkedList** list );

/*
 * Retorna o índice, na lista, do item de dado apontado atualmente pelo cursor.
 * (list não pode ser nulo)
 */

size_t getCursor ( LinkedList** list );

/*
 * Imprime os itens de dados da lista. Se a lista estiver vazia, imprime “Lista vazia”. Note que esta
 * operação é implementada apenas para fins de teste/depuração.
 * (list não pode ser nulo)
 */

void showStructure ( LinkedList** list );

size_t updateCursor( LinkedList** list, const DataType data );

#endif
