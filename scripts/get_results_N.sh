#!/bin/bash -e

if [ $# -eq 1 ] 
then
    Nconst=$1; start=8; step=8; end=8192
elif [ $# -eq 2 ] 
then
    Nconst=$1; start=$2; step=$2; end=8192
elif [ $# -eq 3 ] 
then
    Nconst=$1; start=$2; step=$3; end=8192
elif [ $# -eq 4 ] 
then
    Nconst=$1; start=$2; step=$3; end=$4
else
    Nconst=128; start=8; step=8; end=8192
    if [ $# -ne 0 ] 
    then
        echo "Wrong number of arguments!"
    fi
fi

echo "const N="$Nconst
echo "start="$start "step="$step "end="$end

> 'results_N_const.csv'

for (( i=$start; i<=$end; i+=$step ))
do
    echo $i","$(./a.out --increment $i $Nconst $i) >> 'results_N_const.csv'
done

gnuplot -c gnuplot_commands_N.plt $end $(($end/32))