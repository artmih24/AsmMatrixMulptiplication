#!/bin/bash -e

> 'results_M_2_block_v5.csv'
> 'results_N_2_block_v5.csv'
> 'results_K_2_block_v5.csv'

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment $i 128 128) >> 'results_M_2_block_v5.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 128 $i 128) >> 'results_N_2_block_v5.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 128 128 $i) >> 'results_K_2_block_v5.csv'
done

gnuplot gnuplot_commands_2_block_v5.plt