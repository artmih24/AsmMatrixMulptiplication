#!/bin/bash -e

> './MatrMulV6/results3_M_v6_16384.csv'
> './MatrMulV6/results3_N_v6_16384.csv'
> './MatrMulV6/results3_K_v6_16384.csv'

for i in {8..16384..8}
do
    echo $i" "$(./a.out --increment $i 64 64) >> './MatrMulV6/results3_M_v6_16384.csv'
done

for i in {8..16384..8}
do
    echo $i" "$(./a.out --increment 64 $i 64) >> './MatrMulV6/results3_N_v6_16384.csv'
done

for i in {8..16384..8}
do
    echo $i" "$(./a.out --increment 64 64 $i) >> './MatrMulV6/results3_K_v6_16384.csv'
done

gnuplot gnuplot_commands_3_v6_16384.plt