#!/bin/bash

for i in {25..1200..25}
do
    echo tam: $i
    ./secuencial $i
    ./secuencialmA $i
    ./secuencialmB $i
    ./secuencialmAB $i
done
