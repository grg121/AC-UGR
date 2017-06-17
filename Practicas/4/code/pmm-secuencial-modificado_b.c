/* pmm-secuencial.c
   Producto de dos matrices cuadradas, M y L.
   Para compilar usar (-lrt: real time library)
   gcc  -O2 pmv-secuencial.c -o pmv -lrt
*/

#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h>  // biblioteca donde se encuentra la función clock_gettime()

double **M ;
double **MA ;
double **L ;
double **LA ;
double **R ;
double **RA ;

unsigned int f ;
int i;

const unsigned long BOUND = 64 ;

int main(int argc, char** argv){


    struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución

    //Leer argumento de entrada (nº de filas y columnas)
    if (argc<2){
        printf("Error: Falta el número de filas y columnas.\n");
        exit(-1);
    }
    f = atoi(argv[1]);// Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

    unsigned int fil_tam = sizeof(double) * f ;

    unsigned int fil_lines = fil_tam / BOUND + 1;

    printf("\n\ntamaño de fila: %d, lineas por fila: %d\n\n", fil_tam, fil_lines) ;


    M = (double **)malloc(f*sizeof(double*)) ;
    MA = (double **)malloc(f*sizeof(double*)) ;
    for( i = 0 ; i < f ; i++){
        // reservo una linea más de las necesarias, menos 1B
        MA[i]  =  (double *) malloc(BOUND*(fil_lines+1)-1) ;
        M[i] = (double *) ((((unsigned long) MA[i]) + BOUND-1) & ~(BOUND-1)) ;
    }

    L = (double **)malloc(f*sizeof(double*)) ;
    LA = (double **)malloc(f*sizeof(double*)) ;
    for( i = 0 ; i < f ; i++){
        // reservo una linea más de las necesarias, menos 1B
        LA[i]  =  (double *) malloc(BOUND*(fil_lines+1)-1) ;
        L[i] = (double *) ((((unsigned long) LA[i]) + BOUND-1) & ~(BOUND-1)) ;
    }

    R = (double **)malloc(f*sizeof(double*)) ;
    RA = (double **)malloc(f*sizeof(double*)) ;
    for( i = 0 ; i < f ; i++){
        // reservo una linea más de las necesarias, menos 1B
        RA[i]  =  (double *) malloc(BOUND*(fil_lines+1)-1) ;
        R[i] = (double *) ((((unsigned long) RA[i]) + BOUND-1) & ~(BOUND-1)) ;
    }


    if ( (L==NULL) ||  (M==NULL) || (R==NULL)){
        printf("Error en la reserva de espacio para los vectores\n");
        exit(-2);
    }

    int j ;

    //Inicializar matrices


    for(int i = 0 ; i < f ; i++){
        for(int j = 0 ; j < f ; j++){
            M[i][j] = 2.5*i+j ;
            L[i][j] = i+2.5*j ;
            R[i][j] = 0 ;
        }
    }


    clock_gettime(CLOCK_REALTIME,&cgt1);
    // transposición del a matriz L para eliminar fallos de caché.

    for(i = 0 ; i < f ; i++)
        for(j = 0 ; j < f ; j++){
            if(i < j){
                int aux = L[i][j] ;
                L[i][j] = L[j][i] ;
                L[j][i] = aux ;
            }
        }


    int k ;


    //Calcular multiplicación.
    /*
    for(i=0; i<f; i++){
        for(j=0 ; j<f ; j++){
            for(k=0 ; k<f ; k++){
                R[i][j] += M[i][k]*L[j][k];
            }
        }
    }
    */

#define SM (64/sizeof(double))
    int i2,k2,j2 ;
    double * RR ;
    double * RL ;
    double * RM ;
    for(i = 0 ; i < f ; i += SM)
        for(j = 0 ; j < f ; j += SM)
            for(k = 0 ; k < f ; k += SM)

                for(i2 = 0, RR = &R[i][j], RM = &M[i][j] ;
                    i2 < SM ; ++i2, RR += f, RM += f)
                    for(k2 = 0,  RL = &L[j][k] ; k2 < SM ; ++k2, RL += f)
                        for( j2 = 0 ; j2 < SM ; ++j2)
                            RR[j2] += RM[k2] * RL[j2] ;

    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt+=(double) (cgt2.tv_sec-cgt1.tv_sec)+
        (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));



    printf("\nR[0][0]=%f ; R[n-1][n-1] = %f", R[0][0], R[f-1][f-1]) ;

    ncgt = ncgt ;

    printf("\nTiempo(seg.): %11.9f\t / filas: %u\t / columnas: %u\t",
           ncgt,f,f) ;

    FILE * fp ;
    fp = fopen("salida","a");
    if(fp==NULL){perror("Error opening file.");}
    fprintf(fp,"\nab\t%d\t%f",f,ncgt);
    fclose(fp);

    for(int i = 0 ; i < f ; i++){
        free(MA[i]);
        free(LA[i]);
        free(RA[i]);
    }

    free(M) ; free(MA) ;

    free(L) ; free(LA) ;

    free(R) ; free(RA) ;

}
