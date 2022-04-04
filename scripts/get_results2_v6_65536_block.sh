#!/bin/bash -e

> './MatrMulV6/results3_M_v6_65536_block.csv'
> './MatrMulV6/results3_N_v6_65536_block.csv'
> './MatrMulV6/results3_K_v6_65536_block.csv'

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment $i 64 64) >> './MatrMulV6/results3_M_v6_65536_block.csv'
done

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment 64 $i 64) >> './MatrMulV6/results3_N_v6_65536_block.csv'
done

for i in {8..65536..8}
do
    echo $i" "$(./a.out --increment 64 64 $i) >> './MatrMulV6/results3_K_v6_65536_block.csv'
done

gnuplot gnuplot_commands_3_v6_65536_block.plt