#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define K 1024
#define M 1024*1024
#define DOS_VERA
int* v;

typedef struct ty{
    clock_t tic;
    clock_t toc;

} mytimer;

mytimer* new_mytimer(){
    mytimer* timer = (mytimer*) malloc(sizeof(mytimer));
    timer->tic = 0;
    timer->toc = 0;
    return timer;
}

void start(mytimer* t){
    t->tic = clock();
    t->toc = 0;
}

void stop(mytimer* t){
    if(t->tic != 0)
        t->toc = clock();
    else
    {
        t->tic = 0;
        t->toc = 0;
    }
}

double get_elapsed_time_sec(mytimer* t){
    return (double)(t->toc - t->tic)/CLOCKS_PER_SEC;
}

double get_elapsed_time_microsec(mytimer* t){
    return (double)(t->toc - t->tic);
}

double get_elapsed_time_millisec(mytimer* t){
    return (double)(t->toc - t->tic)/(CLOCKS_PER_SEC/1000);
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(l, m);
        mergeSort(m+1, r);

        merge(l, m, r);
    }
}

/* Function to sort an array using insertion sort*/
void insertionSort(int size)
{
  #ifdef DOS_VERA
   int i, key, j;
   for (i = 1; i < size; i++)
   {
       key = v[i];
       j = i-1;

       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && v[j] > key)
       {
           v[j+1] = v[j];
           j = j-1;
       }
       v[j+1] = key;
   }
   #endif
}

void init1K(){
  v = malloc(sizeof(int)*K);
}

void init100K(){
  v = malloc(sizeof(int)*100*K);
}

void init1M(){
  v = malloc(sizeof(int)*M);
}

void init10M(){
  v = malloc(sizeof(int)*10*M);
}

void init100M(){
  v = malloc(sizeof(int)*100*M);
}

void clear_v(){
  free(v);
}

void insert_ordered(int size){
  int i;
  for(i = 0; i < size; i++){
    v[i] = i;
  }
}

void insert_inverse(int size){
  int i;
  for(i = 0; i < size; i++){
    v[i] = size - i - 1;
  }
}

void shuffle(int size)
{
    if (size > 1)
    {
        int i;
        for (i = 0; i < size - 1; i++)
        {
          int j = i + rand() / (RAND_MAX / (size - i) + 1);
          int t = v[j];
          v[j] = v[i];
          v[i] = t;
        }
    }
}

int main(){

  mytimer* timer = new_mytimer();
  init1K();
  insert_ordered(K);

  start(timer);
  insertionSort(K);
  stop(timer);
  printf("\nTempo de ordenação por inserção para vetor de 1K ordenado: %f\n",get_elapsed_time_millisec(timer));

  insert_inverse(K);

  start(timer);
  insertionSort(K);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 1K reverso: %f\n",get_elapsed_time_millisec(timer));

  shuffle(K);

  start(timer);
  insertionSort(K);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 1K embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

  init100K();
  insert_ordered(100*K);

  start(timer);
  insertionSort(100*K);
  stop(timer);
  printf("\n\nTempo de ordenação por inserção para vetor de 100K ordenado: %f\n",get_elapsed_time_millisec(timer));

  insert_inverse(100*K);

  start(timer);
  insertionSort(100*K);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 100K reverso: %f\n",get_elapsed_time_millisec(timer));

  shuffle(100*K);

  start(timer);
  insertionSort(100*K);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 100K embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

  init1M();
  insert_ordered(M);

  start(timer);
  insertionSort(M);
  stop(timer);
  printf("\n\nTempo de ordenação por inserção para vetor de 1M ordenado: %f\n",get_elapsed_time_millisec(timer));

  insert_inverse(M);

  start(timer);
  insertionSort(M);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 1M reverso: %f\n",get_elapsed_time_millisec(timer));

  shuffle(M);

  start(timer);
  insertionSort(M);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 1M embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

  init10M();
  insert_ordered(10*M);

  start(timer);
  insertionSort(10*M);
  stop(timer);
  printf("\n\nTempo de ordenação por inserção para vetor de 10M ordenado: %f\n",get_elapsed_time_millisec(timer));

  insert_inverse(10*M);

  start(timer);
  insertionSort(10*M);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 10M reverso: %f\n",get_elapsed_time_millisec(timer));

  shuffle(10*M);

  start(timer);
  insertionSort(10*M);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 10M embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

  init1M();
  insert_ordered(100*M);

  start(timer);
  insertionSort(100*M);
  stop(timer);
  printf("\n\nTempo de ordenação por inserção para vetor de 100M ordenado: %f\n",get_elapsed_time_millisec(timer));

  insert_inverse(100*M);

  start(timer);
  insertionSort(100*M);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 100M reverso: %f\n",get_elapsed_time_millisec(timer));

  shuffle(100*M);

  start(timer);
  insertionSort(100*M);
  stop(timer);
  printf("Tempo de ordenação por inserção para vetor de 100M embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();


init1K();
insert_ordered(K);

start(timer);
insertionSort(K);
stop(timer);
printf("\nTempo de ordenação por intercalação para vetor de 1K ordenado: %f\n",get_elapsed_time_millisec(timer));

insert_inverse(K);

start(timer);
insertionSort(K);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 1K reverso: %f\n",get_elapsed_time_millisec(timer));

shuffle(K);

start(timer);
insertionSort(K);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 1K embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

init100K();
insert_ordered(100*K);

start(timer);
insertionSort(100*K);
stop(timer);
printf("\n\nTempo de ordenação por intercalação para vetor de 100K ordenado: %f\n",get_elapsed_time_millisec(timer));

insert_inverse(100*K);

start(timer);
insertionSort(100*K);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 100K reverso: %f\n",get_elapsed_time_millisec(timer));

shuffle(100*K);

start(timer);
insertionSort(100*K);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 100K embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

init1M();
insert_ordered(M);

start(timer);
insertionSort(M);
stop(timer);
printf("\n\nTempo de ordenação por intercalação para vetor de 1M ordenado: %f\n",get_elapsed_time_millisec(timer));

insert_inverse(M);

start(timer);
insertionSort(M);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 1M reverso: %f\n",get_elapsed_time_millisec(timer));

shuffle(M);

start(timer);
insertionSort(M);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 1M embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

init10M();
insert_ordered(10*M);

start(timer);
insertionSort(10*M);
stop(timer);
printf("\n\nTempo de ordenação por intercalação para vetor de 10M ordenado: %f\n",get_elapsed_time_millisec(timer));

insert_inverse(10*M);

start(timer);
insertionSort(10*M);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 10M reverso: %f\n",get_elapsed_time_millisec(timer));

shuffle(10*M);

start(timer);
insertionSort(10*M);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 10M embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();

init1M();
insert_ordered(100*M);

start(timer);
insertionSort(100*M);
stop(timer);
printf("\n\nTempo de ordenação por intercalação para vetor de 100M ordenado: %f\n",get_elapsed_time_millisec(timer));

insert_inverse(100*M);

start(timer);
insertionSort(100*M);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 100M reverso: %f\n",get_elapsed_time_millisec(timer));

shuffle(100*M);

start(timer);
insertionSort(100*M);
stop(timer);
printf("Tempo de ordenação por intercalação para vetor de 100M embaralhado: %f\n",get_elapsed_time_millisec(timer));

clear_v();


}
