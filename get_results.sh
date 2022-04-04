#!/bin/bash -e

#./compile.sh

> 'results_M.csv'
> 'results_N.csv'
> 'results_K.csv'

for i in {8..8192..8}
do
    echo $i","$(./a.out --increment $i 128 128) >> 'results_M.csv'
done

for i in {8..8192..8}
do
    echo $i","$(./a.out --increment 128 $i 128) >> 'results_N.csv'
done

for i in {8..8192..8}
do
    echo $i","$(./a.out --increment 128 128 $i) >> 'results_K.csv'
done

gnuplot gnuplot_commands.plt