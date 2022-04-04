#!/bin/bash -e

N=$1

> 'results_M_1.csv'
> 'results_N_1.csv'
> 'results_K_1.csv'

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment $i 64 64) >> 'results_M_1.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 64 $i 64) >> 'results_N_1.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 64 64 $i) >> 'results_K_1.csv'
done

gnuplot gnuplot_commands_1_v1.plt