#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#define NTHREADS 3

using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
char letra = 'A';
int contador = 0;

void *thread_function(void *id){
    long tid = (long)id;
    printf("Thread number %d\n", tid);
    while(letra <= 'Z')
    {
        pthread_mutex_lock( &mutex1 );

        if(letra > 'Z'){
            pthread_mutex_unlock( &mutex1 );
            break;
        }

        printf("%c", letra);
        contador++;

        pthread_mutex_unlock( &mutex1 );

        if( contador > 2)
        {
            letra++;
            contador = 0;
        }
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
    for(int i = 0; i < NTHREADS; i++)
    {

        pthread_join( thread_id[i], NULL);
    }
    pthread_mutex_destroy(&mutex1);
    return 0;
}
