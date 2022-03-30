#!/bin/bash -e

> './MatrMulV6/results2_M_2_v6_65536.csv'
> './MatrMulV6/results2_N_2_v6_65536.csv'
> './MatrMulV6/results2_K_2_v6_65536.csv'

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment $i 64 64) >> './MatrMulV6/results2_M_2_v6_65536.csv'
done

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment 64 $i 64) >> './MatrMulV6/results2_N_2_v6_65536.csv'
done

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment 64 64 $i) >> './MatrMulV6/results2_K_2_v6_65536.csv'
done

gnuplot gnuplot_commands_2_v6_65536.plt