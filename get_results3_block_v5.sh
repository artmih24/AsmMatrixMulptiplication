#!/bin/bash -e

> './MatrMulV5Block/results2_M_N_block_v5.csv'
> './MatrMulV5Block/results2_N_K_block_v5.csv'
> './MatrMulV5Block/results2_M_K_block_v5.csv'

res=""

res="xxx"
for j in {8..512..8}
do
    res=$res" "$j
done

for i in {8..512..8}
do
    res=$i
    for j in {8..512..8}
    do
        res=$res" "$(./a.out --increment $i $j 64)
    done
    echo $res >> './MatrMulV5Block/results2_M_N_block_v5.csv'
    #echo $i" "$(./a.out --increment $i 128 128) >> './MatrMulV5Block/results_M_3_block_v5.csv'
done

res="xxx"
for j in {8..512..8}
do
    res=$res" "$j
done

for i in {8..512..8}
do
    res=$i
    for j in {8..512..8}
    do
        res=$res" "$(./a.out --increment 64 $i $j)
    done
    echo $res >> './MatrMulV5Block/results2_N_K_block_v5.csv'
    #echo $i" "$(./a.out --increment 128 $i 128) >> './MatrMulV5Block/results_N_3_block_v5.csv'
done

res="xxx"
for j in {8..512..8}
do
    res=$res" "$j
done

for i in {8..512..8}
do
    res=$i
    for j in {8..512..8}
    do
        res=$res" "$(./a.out --increment $i 64 $j)
    done
    echo $res >> './MatrMulV5Block/results2_M_K_block_v5.csv'
    #echo $i" "$(./a.out --increment 128 128 $i) >> './MatrMulV5Block/results_N_3_block_v5.csv'
done

gnuplot gnuplot_commands_3_block_v5.plt