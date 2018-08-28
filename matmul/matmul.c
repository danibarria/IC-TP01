// Introducción a la Concurrencia 2017
// Ejemplo de multiplicación de matrices.
// Programa concurrente.
// Probar distintas ejecuciones cambiando la constante N y
// habilitando o deshabilitando los printf.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

// Hasta N = 381 funciona bien en mi notebook 32bits Dual core, 2GB. Por encima de este valor para N, muestra un error de memoria al crear hilos.
// En una PC 64 bits, cuad core, con 6GB de RAM, el limite es mucho mas grande. Por ejemplo, con 1024 funcionó bien, y tardó unos 6,7 segundos en resolver correctamente la multiplicación.
#define N 512
//#define N 381
    int inicio;    
    int fin;
int numero_parametro, paso;
double a[N][N];
double b[N][N];
double c[N][N];

pthread_t hilos[N];

void iniMat(double mat[][N], int len, double iniVal){
    int i, j;

    for(i = 0; i < len; ++i)
        for(j = 0; j < len; ++j)
            mat[i][j] = iniVal;
}

// Check1Mat: Chequea que la matriz resultante quede con
//            el mismo valor en todas sus celdas.
// Es un chequeo básico para el caso particular en que
// se sabe de ante mano que el resultado tendrá esa forma.
// Retorna: 0 en caso correcto (todas las celdas contiene
//          finVal. 1 En caso de error (al menos una celda
// contiene un valor diferente de finVal).
 
int Check1Mat(double mat[][N], int len, double finVal){
    int i, j;

    for(i = 0; i < len; ++i)
        for(j = 0; j < len; ++j)
            if(mat[i][j] != finVal)
                return 1;
    return 0;
}

void printMat(double mat[][N], int len)
{
    int i, j;

    for(i = 0; i < len; ++i)
    {
        for(j = 0; j < len; ++j)
            printf( "%.1f ", mat[i][j]);
        printf("\n");
    }
}

void *worker(void *arg){
    int i, j, k, tope_w = 0;

    tope_w= (int )arg;
    i  =  tope_w -paso;        
    for(i ; i < tope_w ; i++ ){
        for(j = 0 ; j < N; ++j){
            for(k = 0; k < N; ++k){
                c[i][j] += a[i][k] * b[k][j];        
            }        
        }
    }    
        
            
} 

void mm(int cant_hilos){
    int i, retval;
    paso = N / cant_hilos;
    int tope = 0;
            

    
    for(i = 0; i < cant_hilos ; i++){
        tope = tope + paso; 
        retval = pthread_create(&hilos[i], NULL, &worker, (void *) tope);
        if(retval != 0){
            perror("pthread_create");
            exit(1);
        }
    }

    for(i = 0; i < N; ++i){
        pthread_join(hilos[i], NULL);
    }
}

int main(int argc, char *argv[]){
    printf("Comienzo ...\n");
    iniMat(a, N, 1.0);
    iniMat(b, N, 1.0);
    iniMat(c, N, 0.0);
            
    numero_parametro = atoi(argv[1]);
    
    printf("Multiplicando ...\n" );
    
    mm(numero_parametro);

    if(Check1Mat(c, N, N) == 0)
        printf("Fin Multiplicación (Resultado correcto)\n");
    else
        printf("Fin Multiplicación (Resultado INCORRECTO!)\n");


    printf("Fin del programa\n");
}