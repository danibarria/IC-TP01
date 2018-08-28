#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 2000

char valores[MAX];

int productor;
int consumidor;


void mostrar_caracter(){    
    consumidor = -1;    
    //CONSUMIDOR
    while (consumidor<MAX-1 ){
        if(productor != consumidor ){
            //usleep(20);
            //caso de primer valor / luego el resto de valores
            (productor == 0)? consumidor = 0: consumidor++;               
            printf("CONSUMIDOR:%d -- %c\n", pthread_self(), valores[consumidor]);           
        }
    }    
    pthread_exit(NULL);
}

void caracter_aleatorio(){
    int i = 0;
    productor = -1;  
    //PRODUCTOR
    for(i=0; i < MAX; i++){        
        valores[i] = toascii(65+rand()%55); 
        productor = i;
        printf("id:%d PRODUCTOR:%d %c\n",i, pthread_self(), valores[i]);
        //usleep(15);
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