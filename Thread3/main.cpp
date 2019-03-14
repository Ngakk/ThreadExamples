#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

#define NUM_THREADS     5

 void *wait(void *t)
 {
     long tid = (long)t;
     Sleep(2000);
     printf("Saliendo de dormir de el hilo: %d\n", tid);
     pthread_exit((void*)2); /// <-
     return NULL;
 }

int main()
{
    ///Declaramos variables
    pthread_t threads[NUM_THREADS];
    int rc;
    pthread_attr_t attr;
    void *status;

    ///Inicializamos que existiran threads unibles
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(int i = 0; i < NUM_THREADS; i++)
    {
        ///Creamos hilo
        printf("Creando thread numero: %d \n", i);
                    ///Referencia, NULL, Funcion del hilo, Parametro
        rc = pthread_create(&threads[i], &attr, wait, (void *)i);

        if(rc)
        {
            cout << "Hubo un problema al crear el hilo" << rc << endl;
            exit(-1);
        }
        ///Esperamos a que termine el hilo
        rc = pthread_join(threads[i], &status); ///NULL
        if(rc)
        {
            printf("Error al crear join %d\n", rc);
            exit(-1);
        }
        printf("Hilo completado ID: %d\n", i);
        cout << "  saliendo con estado de:\n" << (int)status << endl;
    }
    /// liberamos attr y esperamos los demas threads
    pthread_attr_destroy(&attr);
    cout << "Programa principal saliendo" << endl;
    pthread_exit(NULL);
    return 0;
}
