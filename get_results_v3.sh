#!/bin/bash -e

N=$1

> 'results_M_v3.csv'
> 'results_N_v3.csv'
> 'results_K_v3.csv'

for i in {16..16384..16}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment $i 64 64)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_M_v3.csv'
done

for i in {16..16384..16}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment 64 $i 64)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_N_v3.csv'
done

for i in {16..16384..16}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment 64 64 $i)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_K_v3.csv'
done