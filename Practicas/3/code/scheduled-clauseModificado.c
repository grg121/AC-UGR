#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

int main(int argc, char **argv) {
    int i, n=200,chunk,a[n],suma=0;
    if(argc < 3)     {
        fprintf(stderr,"\nFalta iteraciones o chunk \n");
        exit(-1);
    }
    n = atoi(argv[1]); if (n>200) n=200; chunk = atoi(argv[2]);

    for (i=0; i<n; i++)       a[i] = i;

    omp_sched_t schedule_type;
    int chunk_size;


    printf("\nAntes de la región parallel\n----------------------\n") ;

    printf("dyn-var: ") ;
    if (omp_get_dynamic()) printf("True\n");
    else printf("False\n");
    printf("nthreads-var: %d\n", omp_get_max_threads());
    printf("thread-limit-var: %d",omp_get_thread_limit());

    omp_get_schedule(&schedule_type, &chunk_size);

    printf("\nrun-sched-var: (modifier) %d (type)",
           chunk_size);

    switch(schedule_type){
    case 1:
        printf("static");
        break;
    case 2:
        printf("dynamic");
        break;
    case 3:
        printf("guided");
        break;
    case 4:
        printf("auto");
        break;
    }

    printf("\n") ;

#pragma omp parallel for firstprivate(suma)     \
    lastprivate(suma) schedule(dynamic,chunk)

    for (i=0; i<n; i++)
    {
        if(i == 0){
            {
                printf("\nDentro de la región parallel\n----------------------\n") ;

                printf("dyn-var: ") ;
                if (omp_get_dynamic()) printf("True\n");
                else printf("False\n");
                printf("nthreads-var: %d\n", omp_get_max_threads());
                printf("thread-limit-var: %d",omp_get_thread_limit());

                omp_get_schedule(&schedule_type, &chunk_size);

                printf("\nrun-sched-var: (modifier) %d (type)",
                       chunk_size);

                switch(schedule_type){
                case 1:
                    printf("static");
                    break;
                case 2:
                    printf("dynamic");
                    break;
                case 3:
                    printf("guided");
                    break;
                case 4:
                    printf("auto");
                    break;
                }

                printf("\n") ;
            }
        }

        suma = suma + a[i];
        printf(" thread %d suma a[%d]=%d suma=%d \n",
               omp_get_thread_num(),i,a[i],suma);

    }

    printf("Fuera de 'parallel for' suma=%d\n",suma);

    return(0);
}
