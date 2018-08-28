    #include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 6

char valores[MAX];
int i ;

void mostrar_Caracter(){    
    for (i = 0 ;  i < MAX ; i++){
        printf("valor:%c ---- hilo:%d\n", valores[i], pthread_self());
    }
}

void caracter_Aleatorio(){
    // coloca valores de 1 a 100 en valores
    for (i = 0 ;  i < MAX ; i++){
        printf("valor:%d hilo:%d\n", i, pthread_self());
        valores[i] = toascii(65+rand()%55);    
    }
}
int main(){
    pthread_t hiloA;
    pthread_t hiloB;

    srand(time(NULL));
    
    //crea el hiloA y ejecuta
    pthread_create(&hiloA, NULL, (void *)caracter_Aleatorio, NULL );    
    
        //espera que termine hiloA
    pthread_join(hiloA, NULL); 

    pthread_create(&hiloB, NULL, (void *)mostrar_Caracter, NULL );
    //espera que termine hiloB

    
    pthread_join(hiloB, NULL);
    pthread_exit(NULL);
    
}