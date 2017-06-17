#!/bin/bash

for i in {500..15000..500}
do
    echo tam: $i
    ./cflops $i
done
