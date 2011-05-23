#!/bin/bash
for t in {1..200..10}
do
    ./main random_list.dat 1 $t single_threaded.dat
done

