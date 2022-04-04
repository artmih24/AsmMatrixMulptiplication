#!/bin/bash -e

> './MatrMulV6/results_M_2_v6.csv'
> './MatrMulV6/results_N_2_v6.csv'
> './MatrMulV6/results_K_2_v6.csv'

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment $i 64 64) >> './MatrMulV6/results_M_2_v6.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 64 $i 64) >> './MatrMulV6/results_N_2_v6.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 64 64 $i) >> './MatrMulV6/results_K_2_v6.csv'
done

gnuplot gnuplot_commands_2_v6.plt