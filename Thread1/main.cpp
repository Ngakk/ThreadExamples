#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>

using namespace std;

#define NUM_THREADS     5

void* ImprimirHola(void* idThread)
{
    long tid = (long)idThread;
    printf("Hello World! Thread ID, %d\n", tid);
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int rc;
    for(int i = 0; i < NUM_THREADS; i++)
    {
        printf("Creando thread numero: %d \n", i);
                    ///Referencia, NULL, Funcion del hilo, Parametro
        rc = pthread_create(&threads[i], NULL, ImprimirHola, (void *)i);

        if(rc)
        {
            cout << "Hubo un problema al crear el hilo" << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
