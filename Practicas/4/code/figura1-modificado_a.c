#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h>  // biblioteca donde se encuentra la función clock_gettime()

int main()
{
    struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución

    int i, ii ;

    struct {
        int a;
        int b;
    } s[5000];

    int X1, X2 ;

    int R[40000] ;

    // inicializar s ;

    for(i = 0 ; i < 5000 ; i++){
        s[i].a = i ;
        s[i].b = 4999 - i ;
    }

    clock_gettime(CLOCK_REALTIME,&cgt1);
    for (ii=0; ii<40000;ii++) {
        X1=0; X2=0;
        for(i=0; i<5000;i++){
            X1+=2*s[i].a+ii;
            X2+=3*s[i].b-ii;
        }
        if (X1<X2)
            R[ii]=X1 ;
        else
            R[ii]=X2;
    }
    clock_gettime(CLOCK_REALTIME,&cgt2);

    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
        (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    // imprimir algunos valores de R:

    for(i = 0 ; i < 40000 ; i+=12345){
        printf("\nR[%d] = %d", i, R[i]) ;
    }

    printf("\n\ntiempo: %f",ncgt) ;

    FILE * fp ;
    fp = fopen("figura1_salida","a");
    if(fp==NULL){perror("Error opening file.");}
    fprintf(fp,"\nmodificadoA\t%f",ncgt);
    fclose(fp);
}
