#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifdef _OPENMP
#include<omp.h>
double vtime ;
#else
#define omp_get_thread_num() 0
struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución
#endif

#define VECTOR_GLOBAL
#ifdef VECTOR_GLOBAL
#define MAX 67108864//=2^26
double v1[MAX], v2[MAX], v3[MAX];
#endif

int main(int argc, char** argv){

    int i;

    //Leer argumento de entrada (nº de componentes del vector)
    if (argc<2){
        printf("Faltan nº componentes del vector\n");
        exit(-1);
    }

    unsigned int N = atoi(argv[1]);
#ifdef VECTOR_LOCAL
    double v1[N], v2[N], v3[N];   // Tamaño variable local en tiempo de ejecución ...
    // disponible en C a partir de actualización C99
#endif
#ifdef VECTOR_GLOBAL
    if (N>MAX) N=MAX;
#endif
#ifdef VECTOR_DYNAMIC
    double *v1, *v2, *v3;
    v1 = (double*) malloc(N*sizeof(double));
    v2 = (double*) malloc(N*sizeof(double));
    v3 = (double*) malloc(N*sizeof(double));
    if ( (v1==NULL) || (v2==NULL) || (v3==NULL) ){
        printf("Error en la reserva de espacio para los vectores\n");
        exit(-2);
    }
#endif

    int Nn = N/4 ;
    // INICIALIZAR VECTORES

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                for(int i = 0 ; i < Nn ; i++){
                    v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
                }
            }
#pragma omp section
            {
                for(int i = Nn ; i < 2*Nn ; i++){
                    v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
                }
            }
#pragma omp section
            {
                for(int i = 2*Nn ; i < 3*Nn ; i++){
                    v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
                }
            }
#pragma omp section
            {
                for(int i = 3*Nn ; i < N ; i++){
                    v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1;
                }
            }

        }
#pragma omp single
        {
#ifdef _OPENMP
            vtime = omp_get_wtime();
#else
            clock_gettime(CLOCK_REALTIME, &cgt1);
#endif
        }

#pragma omp sections
        {
#pragma omp section
            {
                for(int i = 0 ; i < Nn ; i++)
                    v3[i] = v1[i] + v2[i];
            }
#pragma omp section
            {
                    for(int i = Nn ; i < 2*Nn ; i++)
                        v3[i] = v1[i] + v2[i];
            }
#pragma omp section
            {
                    for(int i = 2*Nn ; i < 3*Nn ; i++)
                        v3[i] = v1[i] + v2[i];
            }
#pragma omp section
            {
                    for(int i = 3*Nn ; i < N ; i++)
                        v3[i] = v1[i] + v2[i];
            }

        }
#pragma omp single
        {
#ifdef _OPENMP
            vtime = omp_get_wtime() - vtime;
#else
            clock_gettime(CLOCK_REALTIME, &cgt2);
            ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
                (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
#endif
        }
    }

    //Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    #ifdef _OPENMP
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",vtime,N);
    #else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    #endif
    for(i=0; i<N; i++)
        printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",
               i,i,i,v1[i],v2[i],v3[i]);

#else
    #ifdef _OPENMP
    //printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n", vtime,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);
    //printf("SE HAN CALCULADO LOS TIEMPOS USANDO PARALELISMO CON OPENMP. Usando omp_get_wtime().") ;
    printf("\n%d\t%f\tparalelo (section)",N,vtime);
    #else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n", ncgt,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);
    //printf("SE HA CALCULADO EL TIEMPO SIN UTILIZAR PARALELISMO CON OPENMP, SECUENCIALMENTE. Usando clock_gettime().");
    #endif
#endif


#ifdef VECTOR_DYNAMIC
    free(v1); // libera el espacio reservado para v1
    free(v2); // libera el espacio reservado para v2
    free(v3); // libera el espacio reservado para v3
#endif
    return 0;
}
