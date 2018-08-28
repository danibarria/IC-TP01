#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 10

void caracter_Aleatorio(){
    
    srand(time(NULL));
    char valores[MAX];
    int i ;
    pthread_t thread_self = pthread_self();
    // coloca valores de 1 a 100 en valores
    for (i = 0 ;  i < MAX ; i++){
        valores[i] = toascii(65 + rand()%55);
        printf("valor:%c , hilo:%d\n", valores[i], (int)(pthread_t)thread_self);
    }

    pthread_exit(NULL);    
}


int main(){
    pthread_t hiloA;
    pthread_t hiloB;
    
    pthread_create(&hiloA, NULL, (void *)caracter_Aleatorio, NULL );
    pthread_create(&hiloB, NULL, (void *)caracter_Aleatorio, NULL );
    
    pthread_join(hiloA, NULL);
    pthread_join(hiloB, NULL);
    
    pthread_exit(NULL);
    
}