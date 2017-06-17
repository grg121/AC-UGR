#!/bin/bash

export OMP_NUM_THREADS=12

for i in {2..64..1}
do
    export OMP_SCHEDULE="static, $i"
    echo $OMP_SCHEDULE
    echo
    ./pmtvOMP 153600 >> ./resultados/static
done

for i in {2..64..1}
do
    export OMP_SCHEDULE="dynamic, $i"
    echo $OMP_SCHEDULE
    echo
    ./pmtvOMP 153600 >> ./resultados/dynamic
done

for i in {2..64..1}
do
    export OMP_SCHEDULE="guided, $i"
    echo $OMP_SCHEDULE
    echo
    ./pmtvOMP 153600 >> ./resultados/guided
done
