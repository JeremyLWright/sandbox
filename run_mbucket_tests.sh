#!/bin/bash
rm multi_threaded.dat
for t in {100..10000..100}
do
    ./mbucket_sort random_list.dat $t multi_threaded.dat
done
