#!/bin/bash -e

N=$1

> 'results_M_1_big.csv'
> 'results_N_1_big.csv'
> 'results_K_1_big.csv'

for i in {8..81920..8}
do
    echo $i" "$(./a.out --increment $i 64 64) >> 'results_M_1_big.csv'
done

for i in {8..81920..8}
do
    echo $i" "$(./a.out --increment 64 $i 64) >> 'results_N_1_big.csv'
done

for i in {8..81920..8}
do
    echo $i" "$(./a.out --increment 64 64 $i) >> 'results_K_1_big.csv'
done

gnuplot gnuplot_commands_1_v1_big.plt