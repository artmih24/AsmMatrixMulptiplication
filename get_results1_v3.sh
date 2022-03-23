#!/bin/bash -e

N=$1

> 'results_M_1_v3.csv'
> 'results_N_1_v3.csv'
> 'results_K_1_v3.csv'

for i in {16..16384..16}
do
    echo $i" "$(./a.out --increment $i 64 64) >> 'results_M_1_v3.csv'
done

for i in {16..16384..16}
do
    echo $i" "$(./a.out --increment 64 $i 64) >> 'results_N_1_v3.csv'
done

for i in {16..16384..16}
do
    echo $i" "$(./a.out --increment 64 64 $i) >> 'results_K_1_v3.csv'
done