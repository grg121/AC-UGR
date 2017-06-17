#!/bin/bash

for i in {1..100..1}
do
    echo tam: $i
    ./daxpy3
    ./daxpy0
    ./daxpy1
    ./daxpy2
done
