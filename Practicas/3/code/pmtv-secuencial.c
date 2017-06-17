/* pmtv-secuencial.c
   Producto de una matriz cuadrada M triangular por un vector v1
   Para compilar usar (-lrt: real time library)
   gcc  -O2 pmv-secuencial.c -o pmv -lrt
*/

#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h>  // biblioteca donde se encuentra la función clock_gettime()


int main(int argc, char** argv){

    int i;

    struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución

    //Leer argumento de entrada (nº de componentes del vector)
    if (argc<2){
        printf("Error: Falta el número de filas y columnas.\n");
        exit(-1);
    }
    unsigned int f = atoi(argv[1]);// Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)

    double **M = (double **)malloc(f*sizeof(double*)) ;
    for( i = 0 ; i < f ; i++) M[i] = (double*)malloc(f * sizeof(double)) ;
    double *v1, *v2 ;
    v1 = (double*) malloc(f*sizeof(double));// malloc necesita el tamaño en bytes
    v2 = (double*) malloc(f*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
    if ( (v1==NULL) || (v2==NULL) || (M==NULL) ){
        printf("Error en la reserva de espacio para los vectores\n");
        exit(-2);
    }


    //Inicializar vector
    for(i=0; i<f; i++){
        v1[i] = 1.0;
    }
    //Inicializar matriz
    int j ;
    for(i=0 ; i < f ; i++)
        for(j = 0 ; j < f ; j++){
            if(i>j)
                M[i][j] = 0;
            else
                M[i][j] = 2.0;
        }

    int h ;
    int VECES = 100 ;
    for(h = 0 ; h < VECES ; h++){
    clock_gettime(CLOCK_REALTIME,&cgt1);

    //Calcular multiplicación.
    for(i=0; i<f; i++){
        v2[i] = 0 ;
        for(j=i ; j<f ; j++){
            v2[i] += M[i][j]*v1[j] ;
        }
    }
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt+=(double) (cgt2.tv_sec-cgt1.tv_sec)+
        (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    int k ;

    if(h%100==0){

        printf("\n%d\n",h) ;
    for(k = 0 ; k < f ; k=k+f-1){
        printf("\nv1[%d]=  %11.3f",k,v1[k]);
    }

    for(k=0 ; k < f ; k=k+f-1)
        printf("\nM[1][%d]=%11.3f",k,M[1][k]);
    for(k=0 ; k < f ; k=k+f-1)
        printf("\nv2[%d]=  %11.3f",k,v2[k]);
        }
    }
    ncgt = ncgt/VECES ;
    printf("\nTiempo(seg.): %11.9f\t / filas: %u\t / columnas: %u\t",
           ncgt,f,f) ;

    FILE * fp ;
    fp = fopen("salida","a");
    if(fp==NULL){perror("Error opening file.");}
    fprintf(fp,"\n%d\t%f",f,ncgt);
    fclose(fp);


#ifdef VECTOR_DYNAMIC
            for(i = 0 ; i < f ; i++)
                free(M[i]) ;
            free(M) ;
    free(v1); // libera el espacio reservado para v1
    free(v2); // libera el espacio reservado para v2
#endif
    return 0;
}
