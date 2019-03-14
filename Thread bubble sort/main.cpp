#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#define NTHREADS 5
#define NVALUES 70000

using namespace std;
int valores[5][NVALUES];

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

void OrdenamientoBurbuja(int *_lista, int _size)
{
    bool unordered = true;
    while(unordered)
    {
        unordered = false;
        for(int i = 0; i < _size-1; i++){
            int val1 = _lista[i];
            int val2 = _lista[i+1];
            if(val2 > val1){
                _lista[i] = val2;
                _lista[i+1] = val1;
                unordered = true;
            }
        }
    }
}

void* thread_function(void *id)
{
    long tid = (long)id;
    printf("Thread number %d\n", tid);

    ///Defining cycles
    int times = ceil((double)NVALUES/(double)NTHREADS);
    if(NVALUES%NTHREADS <= tid && NVALUES%NTHREADS != 0)
        times--;



    return NULL;
}

int main()
{
    //Init
    srand( time(NULL) );

    printf("Filling arrays...\n");
    for(int i = 0; i < NVALUES; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            valores[j][i] = (rand()%200000) - 100000;
        }
    }

    system("cls");
    printf("Ordering on main...");

    Start_record();
    for(int i = 0; i < 5; i++)
        OrdenamientoBurbuja(valores[i], NVALUES);
    Stop_record();

    /*printf("Ordering on threads...");
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
    }*/

    return 0;
}
