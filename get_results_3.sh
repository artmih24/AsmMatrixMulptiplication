#!/bin/bash -e

> 'results_3_M_N.csv'
> 'results_3_N_K.csv'
> 'results_3_M_K.csv'

res=""

res="xxx"
for j in {8..256..8}
do
    res=$res" "$j
done
echo $res >> 'results_3_M_N.csv'

for i in {8..256..8}
do
    res=$i
    for j in {8..256..8}
    do
        res=$res" "$(./a.out --increment $i $j 64)
    done
    echo $res >> 'results_3_M_N.csv'
done

res="xxx"
for j in {8..256..8}
do
    res=$res" "$j
done
echo $res >> 'results_3_N_K.csv'

for i in {8..256..8}
do
    res=$i
    for j in {8..256..8}
    do
        res=$res" "$(./a.out --increment 64 $i $j)
    done
    echo $res >> 'results_3_N_K.csv'
done

res="xxx"
for j in {8..256..8}
do
    res=$res" "$j
done
echo $res >> 'results_3_M_K.csv'

for i in {8..256..8}
do
    res=$i
    for j in {8..256..8}
    do
        res=$res" "$(./a.out --increment $i 64 $j)
    done
    echo $res >> 'results_3_M_K.csv'
done

gnuplot gnuplot_commands_3.plt