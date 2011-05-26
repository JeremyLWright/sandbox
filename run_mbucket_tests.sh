#!/bin/bash
rm multi_threaded.dat
for t in {100..500..100}
do
    ./main random_list.dat 10 $t multi_threaded.dat
done
