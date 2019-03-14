#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#define NTHREADS 10

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int contador = 0;

using namespace std;

void *thread_function(void *id)
{
    long tid = (long)pthread_self(); ///Su propio id, que es 1
    printf("Thread number %d\n", tid);
    while(contador < 10000)
    {
        pthread_mutex_lock( &mutex1 );
        if(contador >= 10000)
        {
            pthread_mutex_unlock( &mutex1 ); ///NO OLVIDARLO
            break;
        }
        contador++;
        printf("%d - subi a %d\n", tid, contador);
        pthread_mutex_unlock( &mutex1 );
        Sleep(1); ///SE PUEDE OMITIR
    }
    return NULL;
}

int main()
{
    pthread_t thread_id[NTHREADS];
    pthread_mutex_init(&mutex1, NULL); //Viejo
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
    pthread_mutex_destroy(&mutex1); //Viejo
    printf("Valor final del contador %d\n", contador);
    return 0;
}
