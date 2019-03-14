#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#define NTHREADS 5
#define NVALUES 49

using namespace std;
int valores[NVALUES];


void* thread_function(void *id)
{
    long tid = (long)id;
    printf("Thread number %d\n", tid);
    ///Defining cycles
    int times = ceil((double)NVALUES/(double)NTHREADS);
    if(NVALUES%NTHREADS <= tid && NVALUES%NTHREADS != 0)
        times--;
    ///Populating

    for(int contador = 0; contador < times; contador++){
        srand( time(NULL) + tid);
        int pos = contador*NTHREADS + tid;
        valores[pos] = (rand() % 100) + 1;
        printf("Hilo %d agrego: %d en posicion %d\n", tid, valores[contador], pos);
        Sleep(1);
    }
    return NULL;
}

int main()
{
    srand( time(NULL) );

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

    int temp = 0;
    for(int i = 0; i < NVALUES; i++)
    {
        temp += valores[i];
    }
    printf("La suma de los valores es: %d", temp);
    return 0;
}
