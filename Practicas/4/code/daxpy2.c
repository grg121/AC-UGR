/* Ejemplo de Programa de Prueba */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include<stdlib.h>


int suma_prod(int a, int b, int n)
{
    return a * b + n;
}

int main(int argc, char * argv[])
{
    int i,j,a,b,n,c;

    clock_t start,stop;

    //Leer argumento de entrada (nº de filas y columnas)
    if (argc<2){
        printf("Error: Falta el tamaño del problema.\n");
        exit(-1);
    }

    n=6000;a=1;b=2;

    int size = atoi(argv[1]);

    double tt = 0 ;

    for(int i = 0 ; i < 20 ; i++){
    start = clock();

    for (j=1;j<=size;j++)
    {
        printf("a=%d b=%d n=%d\n",a,b,n);
        c=suma_prod(a,b,n);
        printf("resultado= %d\n",c);
    }

    stop = clock();

    double tiempo = difftime(stop,start) / (CLOCKS_PER_SEC / 1000.0) ;
    tt+=tiempo ;

    }

    tt = (double) tt/20 ;


    FILE * fp ;
    fp = fopen("tf.dat","a");
    if(fp==NULL){perror("Error opening file.");}
    fprintf(fp,"\n%d\t%f",size,tt);
    fclose(fp);

    return 0;

}
