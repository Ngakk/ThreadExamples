#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#define NTHREADS 5
#define NVALUES 500000

using namespace std;
int valores[NVALUES];
int biggest[NTHREADS];

///Ayudara a tomar tiempo de procesamiento
clock_t start, endt;
double msecs;
void Start_record()
{
    start = clock();
}
void Stop_record()
{
    endt = clock();
    msecs = ((double) (endt - start)) / CLOCKS_PER_SEC;
    cout << msecs << " ms" << endl;
}

void* thread_function(void *id)
{
    long tid = (long)id;
    printf("Thread number %d\n", tid);

    ///Defining cycles
    int times = ceil((double)NVALUES/(double)NTHREADS);
    if(NVALUES%NTHREADS <= tid && NVALUES%NTHREADS != 0)
        times--;

    int currentBiggest = -10000;

    for(int contador = 0; contador < times; contador++)
    {
        int pos = contador*NTHREADS + tid;
        if(valores[pos] > currentBiggest)
            currentBiggest = valores[pos];
        //Sleep(1);
    }

    biggest[tid] = currentBiggest;

    return NULL;
}

int main()
{
    //Init
    srand( time(NULL) );

    printf("Starting to fill\n");
    Start_record();
    for(int i = 0; i < NVALUES; i++)
    {
        valores[i] = (rand()%20000) - 10000;
        /*system("cls");*/
        //printf("%d \n", valores[i]);
    }
    Stop_record();
    printf("Fill ended\n");

    pthread_t thread_id[NTHREADS];
    ///Creo hilos
    for(int i = 0; i < NTHREADS; i++)
    {
        pthread_create( &thread_id[i], NULL, thread_function, (void *)i );
    }
    ///Esperamos que terminen
    for(int i=0; i < NTHREADS; i++)
    {
        pthread_join( thread_id[i], NULL);
    }

    int biggestFinal = -10000;
    for(int i = 0; i < NTHREADS; i++){
        if(biggest[i] > biggestFinal)
            biggestFinal = biggest[i];
    }

    printf("Biggest number was %d\n", biggestFinal);


    return 0;
}
