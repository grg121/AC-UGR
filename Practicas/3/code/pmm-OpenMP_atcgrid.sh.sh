#!/bin/bash

for i in {1..14..1}
do
    echo cores: $i
    export OMP_NUM_THREADS=$i
    ./pmmOMP 100 $i atcgrid
    ./pmmOMP 1500 $i atcgrid
done
