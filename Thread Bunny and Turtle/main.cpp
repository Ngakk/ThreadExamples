#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#define NTHREADS 2

using namespace std;

int turtle = 1, bunny = 1;
int goal = 70;


int AvanceRapido = 3;
int Resbalo = -6;
int AvanceLento = 1;

int Duerme = 0;
int GranSalto = 9;
int ResbalonGrande = -12;
int PequenoSalto = 1;
int ResbalonPequeno = -2;

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
    cout << msecs << " s" << endl;
}

void* thread_function(void *id)
{
    long tid = (long)id;
    printf("Thread number %d\n", tid);

    while(turtle < 70 && bunny < 70)
    {
        if(tid == 1)
        {
            //Es tortuga
            int c = (rand() % 100) + 1;

            if(c <= 50) {
                turtle += AvanceRapido;
                printf("Tortug + %d, ahora en %d.\n", AvanceRapido, turtle);
            }
            else if (c <= 70){
                turtle += Resbalo;
                if(turtle < 1) turtle = 1;
                printf("Tortug - %d, ahora en %d.\n", -Resbalo, turtle);
            }
            else {
                turtle += AvanceLento;
                printf("Tortug + %d, ahora en %d.\n", AvanceLento, turtle);
            }


        }
        else
        {
            //Es conejo
            int c = (rand() % 100) + 1;

            if(c <= 20) {
                bunny += Duerme;
                printf("Conejo + %d, ahora en %d.\n", Duerme, bunny);
            }
            else if(c <= 40){
                bunny += GranSalto;
                printf("Conejo + %d, ahora en %d.\n", GranSalto, bunny);
            }
            else if(c <= 50) {
                bunny += ResbalonGrande;
                if(bunny < 1) bunny = 1;
                printf("Conejo - %d, ahora en %d.\n", -ResbalonGrande, bunny);
            }
            else if(c <= 80) {
                bunny += PequenoSalto;
                printf("Conejo + %d, ahora en %d.\n", PequenoSalto, bunny);
            }
            else {
                bunny += ResbalonPequeno;
                if(bunny < 1) bunny = 1;
                printf("Conejo - %d, ahora en %d.\n", -ResbalonPequeno, bunny);
            }


        }
        Sleep(200);
    }

    return NULL;
}

int main()
{
    srand( time(NULL) );
    pthread_t thread_id[NTHREADS];

    Start_record();
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
    Stop_record();

    if(turtle >= goal && bunny >= goal){
        printf("EMPATE?!?!?!?!?");
    }
    else if(turtle >= goal){
        printf("Tortuga gana con %d vs conejo con %d.", turtle, bunny);
    }
    else if(bunny >= goal){
        printf("Conejo gana con %d vs tortuga con %d.", bunny, turtle);
    }
    else{
        printf("No se que paso.");
    }

    return 0;
}
