#!/bin/bash
rm single_threaded.dat
for t in {100..10000..100}
do
    nice -20 ./sbucket_sort random_list.dat $t single_threaded.dat
done
