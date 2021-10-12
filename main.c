#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define N 10000000

#define NUM_THREADS 2

int A[N] = {0};

void *llena_arreglo_izq(void *threadid) {
    for(int i = 0; i < N; ++i)
    {
//        printf("Voy en la posición: %d (izq)\n", i);
        if(A[i] == 1)
            break;
        else
        {
                A[i] = 1;
        }
    }
    pthread_exit(NULL);
}


void *llena_arreglo_der(void *threadid) {

    for(int i = N - 1; i >= 0; --i)
    {
//        printf("Voy en la posición: %d (der)\n", i);
        if(A[i] == 1)
            break;
        else
        {
                A[i] = 1;
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    clock_t t;
//    t = clock();
//
//
//    for(int i = 0; i < N; ++i)
//        A[i] = 1;
//
//    t = clock() - t;
//
//    double tiempo = ((double)t) / CLOCKS_PER_SEC;
//    printf("Tiempo utilizado: %f\n", tiempo); //0.47318s

    t = clock();

    for(int i = 0; i < NUM_THREADS / 2; i++ ) {
        ids[i] = i;
        //printf("main() : creating thread, %d\n", i);
        int rc = pthread_create(&threads[i], NULL, llena_arreglo_izq, &ids[i]);
        ++i;
        ids[i] = i;
        //printf("main() : creating thread, %d\n", i);
        int rc2 = pthread_create(&threads[i], NULL, llena_arreglo_der, &ids[i]);
        if (rc || rc2) {
            printf("Error:unable to create thread, %d\n", rc);
            exit(-1);
        }
    }
    for(int i = 0; i < NUM_THREADS; i++ ) {
        pthread_join(threads[i], 0);
    }
    t = clock() - t;

    double tiempo = ((double)t) / CLOCKS_PER_SEC;
    printf("Tiempo utilizado_2: %f\n", tiempo); //0.104276s

    return 0;

    for(int i = 0; i < N; ++i)
    {
        if(A[i] != 1)
            puts("F");
    }
    puts("GEÑAL");
    return 0;
}
