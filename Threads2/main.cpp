#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_THREADS     8

using namespace std;

char *mensajes[NUM_THREADS];

struct thread_data
{
    int thread_id;
    int sum;
    char *message;
};

struct thread_data thread_data_array[NUM_THREADS]; ///declaro arreglo de thread_data

void *PrintHello(void *argumento) ///Funcion para los hilos
{
    ///Variables para almacenar los daros que recibe el hilo
    int taskid, sum;
    char *hello_msg;
    struct thread_data *my_data;

    Sleep(1); ///El hilo se duerme un milisegundo
    ///Casteamos a la estructura y pasamos datos a variables locales
    my_data = (struct thread_data *) argumento;
    taskid = my_data->thread_id;
    sum = my_data->sum;
    hello_msg = my_data->message;
    ///Imprimo datos
    printf("Thread %d: %s Sum = %d\n", taskid, hello_msg, sum);
    return NULL;
}

int main()
{
    ///Declaro variables
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc, t, sum;
    sum=0;
    ///Preparo mensajes
    mensajes[0] = "English: Hello World!";
    mensajes[1] = "French: Bonjour, le monde!";
    mensajes[2] = "Spanish: Hola mundo!";
    mensajes[3] = "Klingon: Nug neH!";
    mensajes[4] = "German: Guten Tag, Welt";
    mensajes[5] = "Russian: Zdravstvytye, mir";
    mensajes[6] = "Japan: Sekai e konnichiwa!";
    mensajes[7] = "Latin: Orbis, te saluto!";

    ///For para crear hilos
    for(t=0; t < NUM_THREADS; t++)
    {
        sum = sum + t; ///Aumentamos el valor de la suma

        ///Agregago datos a mi estructura
        thread_data_array[t].thread_id = t;
        thread_data_array[t].sum = sum;
        thread_data_array[t].message = mensajes[t];
        printf("Creando hilo %d\n", t);
        ///Creamos hilo
        rc = pthread_create(&threads[t], NULL, PrintHello, (void*)&thread_data_array[t]);
        if(rc)
        {
            printf("Error al crear hilo %d\n", rc);
        }
    }
    pthread_exit(NULL);
    return 0;
}
