#!/bin/bash -e

> './MatrMulV5Block/results_M_2_block_v5_65536.csv'
> './MatrMulV5Block/results_N_2_block_v5_65536.csv'
> './MatrMulV5Block/results_K_2_block_v5_65536.csv'

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment $i 128 128) >> './MatrMulV5Block/results_M_2_block_v5_65536.csv'
done

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment 128 $i 128) >> './MatrMulV5Block/results_N_2_block_v5_65536.csv'
done

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment 128 128 $i) >> './MatrMulV5Block/results_K_2_block_v5_65536.csv'
done

gnuplot gnuplot_commands_2_block_v5_65536.plt