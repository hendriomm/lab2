#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KILO 1024
#define MEGA 1024
#define GIGA 1024

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

void workload1K(){
    long int i,j,k;
    for(i = 0, j = 0;i < KILO; i++,j--){
       // k = i + j;
    }
}

void workload1M(){
    long int i,j,sum;
    for(i = 0;i < MEGA; i++){
        for(j = 0;j < MEGA; j++){
            //sum = i + j;
        }
    }
}

void workload1G(){
    long long i,j,k,l,sum;
    sum = 0;
    for(i = 0;i < GIGA; i++){
        for(j = 0;j < GIGA; j++){
            for(k = 0;k < GIGA; k++){
                for(l = 0;l < GIGA; l++){
                    //sum = i + j + k + l;
                }
            }
        }
    }
}

int main(){
    mytimer* timer = new_mytimer();

    printf("\n Workload: 1K\n\n");
    start(timer);
    workload1K();
    stop(timer);
    printf("elapsed time: %f seconds\n",get_elapsed_time_sec(timer));
    printf("elapsed time: %f milliseconds\n",get_elapsed_time_millisec(timer));
    printf("elapsed time: %f microseconds\n",get_elapsed_time_microsec(timer));

    printf("\n Workload: 1M\n\n");
    start(timer);
    workload1M();
    stop(timer);
    printf("elapsed time: %f seconds\n",get_elapsed_time_sec(timer));
    printf("elapsed time: %f milliseconds\n",get_elapsed_time_millisec(timer));
    printf("elapsed time: %f microseconds\n",get_elapsed_time_microsec(timer));

    printf("\n Workload: 1G\n\n");
    start(timer);
    workload1G();
    stop(timer);
    printf("elapsed time: %f seconds\n",get_elapsed_time_sec(timer));
    printf("elapsed time: %f milliseconds\n",get_elapsed_time_millisec(timer));
    printf("elapsed time: %f microseconds\n",get_elapsed_time_microsec(timer));

    free(timer);
    
}
