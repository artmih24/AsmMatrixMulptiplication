#!/bin/bash -e

#./compile.sh

if [ $# -eq 1 ] 
then
    if [ $1 -ge 64 ]
    then
        Mconst=128; Nconst=128; Kconst=128; start=8; step=8; end=$1
    else
        Mconst=$1; Nconst=$1; Kconst=$1; start=8; step=8; end=8192
    fi
elif [ $# -eq 2 ] 
then
    if [ $2 -ge 64 ]
    then
        Mconst=$1; Nconst=$1; Kconst=$1; start=8; step=8; end=$2
    else
        Mconst=$1; Nconst=$1; Kconst=$1; start=$2; step=$2; end=8192
    fi
elif [ $# -eq 3 ] 
then
    if [ $3 -ge 64 ]
    then
        Mconst=$1; Nconst=$1; Kconst=$1; start=$2; step=$2; end=$3
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=8; step=8; end=8192
    fi
elif [ $# -eq 4 ] 
then
    if [ $4 -ge 64 ]
    then
        Mconst=$1; Nconst=$2; Kconst=$3; start=8; step=8; end=$4
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$4; end=8192
    fi
elif [ $# -eq 5 ] 
then
    if [ $5 -ge 64 ]
    then
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$4; end=$5
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$5; end=8192
    fi
elif [ $# -eq 6 ] 
then
    Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$5; end=$6
else
    Mconst=128; Nconst=128; Kconst=128; start=8; step=8; end=8192
    echo "Default values"
    if [ $# -ne 0 ] 
    then
        echo "Wrong number of arguments!"
    fi
fi

echo "const M = "$Mconst", N = "$Nconst", K = "$Kconst
echo "start = "$start", step = "$step", end = "$end

> 'results.csv'

for (( i=$start; i<=$end; i+=$step ))
do
    PerformanceM=$(./a.out --increment $i $Nconst $Kconst)
    PerformanceN=$(./a.out --increment $Mconst $i $Kconst)
    PerformanceK=$(./a.out --increment $Mconst $Nconst $i)
    echo $i","$PerformanceM","$PerformanceN","$PerformanceK >> 'results.csv'
done

gnuplot -c gnuplot_commands.plt $end $(($end/32))