// %%writefile ej2.c

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

void main(){
        srand(time(NULL));
        int valores[MAX];
        int i ;
        // coloca valores de 1 a 100 en valores
        for (i = 0 ;  i < MAX ; i++){
            valores[i] = (rand()%100+1);
        }
        // recorre el arreglo
        for ( i = 0 ; i < MAX ; i ++){
            printf("\n%d", valores[i]);
        }    
}