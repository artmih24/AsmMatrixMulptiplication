#!/bin/bash -e

#./compile.sh

> './MatrMulV6/results3_M_v6_16384_block.csv'
> './MatrMulV6/results3_N_v6_16384_block.csv'
> './MatrMulV6/results3_K_v6_16384_block.csv'

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment $i 128 128) >> './MatrMulV6/results3_M_v6_16384_block.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 128 $i 128) >> './MatrMulV6/results3_N_v6_16384_block.csv'
done

for i in {8..8192..8}
do
    echo $i" "$(./a.out --increment 128 128 $i) >> './MatrMulV6/results3_K_v6_16384_block.csv'
done

gnuplot gnuplot_commands_3_v6_16384_block.plt