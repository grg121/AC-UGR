#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h>  // biblioteca donde se encuentra la función clock_gettime()
#include <xmmintrin.h>


int main()
{
    struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución

    int i, ii ;

    struct {
        int a;
        int b;
    } s[5000];

    int X1, X2 ;

    struct{
        int x1;
        int x2;
    } x[5000] ;

    int R[40000] ;

    // inicializar s ;

    for(i = 0 ; i < 5000 ; i++){
        s[i].a = i ;
        s[i].b = 4999 - i ;
    }

    clock_gettime(CLOCK_REALTIME,&cgt1);
    for(i = 0 ; i < 5000 ; i++){
        x[i].x1 = 0 ; x[i].x2 = 0 ;
        x[i].x1 = s[i].a+s[i].a; //x2
        x[i].x2 = s[i].b+s[i].b+s[i].b ; //x3
    }
    for (ii=0; ii<40000;ii++) {
        X1=0; X2=0;
        for(i=0; i<5000;i++){
            X1+=x[i].x1+ii;
            X2+=x[i].x2-ii;
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
    fprintf(fp,"\nmodificadoAB\t%f",ncgt);
    fclose(fp);
}
