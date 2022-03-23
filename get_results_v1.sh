#!/bin/bash -e

N=$1

> 'results_M.csv'
> 'results_N.csv'
> 'results_K.csv'

for i in {8..8192..8}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment $i 64 64)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_M.csv'
done

for i in {8..8192..8}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment 64 $i 64)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_N.csv'
done

for i in {8..8192..8}
do
    res=0
    for (( j=0; j<$N; j+=1))
    do
        res=$(bc<<<"scale=3;$res+$(./a.out --increment 64 64 $i)")
    done
    echo $i" "$(bc<<<"scale=3;$res/$N") >> 'results_K.csv'
done