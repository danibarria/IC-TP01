/*version con punteros - supongo que era opcional*/

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 20

char valores[MAX];

char *productor;
char *consumidor;


void mostrar_caracter(){    
    int j = 0;
    consumidor = NULL;    
    //CONSUMIDOR
    while (j<MAX-1 ){
        
        if(productor != consumidor){
            usleep(20);
            //caso de primer valor / luego el resto de valores
            (productor == &valores[0])? consumidor = &valores[0]: consumidor++;              
            j++; 
            printf("CONSUMIDOR:%d -- %c\n", pthread_self(), *consumidor);           
        }
    }    
    pthread_exit(NULL);
}

void caracter_aleatorio(){
    int i = 0;
    productor = NULL;  
    //PRODUCTOR
    for(i=0; i < MAX; i++){        
        valores[i] = toascii(65+rand()%55); 
        productor = &valores[i];
        printf("PRODUCTOR:%d %c\n", pthread_self(), valores[i]);
        usleep(20);
    }
    
    pthread_exit(NULL);
}
               
int main(){
    pthread_t hiloA;
    pthread_t hiloB;

    srand(time(NULL));   
    
    pthread_create(&hiloA, NULL, (void *)caracter_aleatorio, NULL );
    pthread_create(&hiloB, NULL, (void *)mostrar_caracter, NULL );  
    pthread_exit(NULL);
    
}
