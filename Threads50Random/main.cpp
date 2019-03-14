#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define NTHREADS 5
#define NVALUES 50

using namespace std;
int valores[NVALUES];
int contador = 0;

void* thread_function(void *id)
{
    long tid = (long)id;
    printf("Thread number %d\n", tid);
    while(contador < NVALUES){
        srand( time(NULL) + contador );
        valores[contador] = (rand() % 100) + 1;
        printf("Hilo %d agrego: %d\n", tid, valores[contador]);
        Sleep(1);
        contador++;
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
