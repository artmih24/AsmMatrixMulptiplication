#!/bin/bash -e

#./compile.sh

if [ $# -eq 1 ] 
then
    if [ $1 -ge 4096 ]
    then
        Mconst=128; Nconst=128; Kconst=128; start=8; step=8; end=$1
    else
        Mconst=$1; Nconst=$1; Kconst=$1; start=8; step=8; end=2048
    fi
elif [ $# -eq 2 ] 
then
    if [ $2 -ge 64 ]
    then
        Mconst=$1; Nconst=$1; Kconst=$1; start=8; step=8; end=$2
    else
        Mconst=$1; Nconst=$1; Kconst=$1; start=$2; step=$2; end=2048
    fi
elif [ $# -eq 3 ] 
then
    if [ $3 -ge 4096 ]
    then
        Mconst=$1; Nconst=$1; Kconst=$1; start=$2; step=$2; end=$3
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=8; step=8; end=2048
    fi
elif [ $# -eq 4 ] 
then
    if [ $4 -ge 64 ]
    then
        Mconst=$1; Nconst=$2; Kconst=$3; start=8; step=8; end=$4
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$4; end=2048
    fi
elif [ $# -eq 5 ] 
then
    if [ $5 -ge 64 ]
    then
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$4; end=$5
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$5; end=2048
    fi
elif [ $# -eq 6 ] 
then
    Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$5; end=$6
else
    Mconst=128; Nconst=128; Kconst=128; start=8; step=8; end=2048
    echo "Default values"
    if [ $# -ne 0 ] 
    then
        echo "Wrong number of arguments!"
    fi
fi

echo "---- Bash script ----"
echo "const M = "$Mconst", N = "$Nconst", K = "$Kconst
echo "start = "$start", step = "$step", end = "$end

echo "M/N/K,Performance(M-N),Performance(M-K),Performance(N-K)" > 'results_2.csv'

for (( i=$start; i<=$end; i+=$step ))
do
    PerformanceMN=$(./a.out --increment $i $i $Kconst)
    PerformanceMK=$(./a.out --increment $i $Nconst $i)
    PerformanceNK=$(./a.out --increment $Mconst $i $i)
    echo $i","$PerformanceMN","$PerformanceMK","$PerformanceNK >> 'results_2.csv'
done

gnuplot -c gnuplot_commands_2.plt $end $(($end/32))