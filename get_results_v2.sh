#!/bin/bash -e

N=$1

> 'results_M_v2.csv'
> 'results_N_v2.csv'
> 'results_K_v2.csv'

for i in {8..8192..8}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment $i 64 64)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_M_v2.csv'
done

for i in {8..8192..8}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment 64 $i 64)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_N_v2.csv'
done

for i in {8..8192..8}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment 64 64 $i)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_K_v2.csv'
done

gnuplot gnuplot_commands_v2.plt