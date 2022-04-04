#!/bin/bash -e

#./compile.sh

if [ $# -eq 1 ] 
then
    Mconst=$1
    Nconst=$1
    Kconst=$1
    start=8
    step=8
    end=8192
elif [ $# -eq 2 ] 
then
    Mconst=$1
    Nconst=$1
    Kconst=$1
    start=$2
    step=$2
    end=8192
elif [ $# -eq 3 ] 
then
    Mconst=$1
    Nconst=$2
    Kconst=$3
    start=8
    step=8
    end=8192
elif [ $# -eq 4 ] 
then
    Mconst=$1
    Nconst=$2
    Kconst=$3
    start=$4
    step=$4
    end=8192
elif [ $# -eq 5 ] 
then
    Mconst=$1
    Nconst=$2
    Kconst=$3
    start=$4
    step=$5
    end=8192
elif [ $# -eq 6 ] 
then
    Mconst=$1
    Nconst=$2
    Kconst=$3
    start=$4
    step=$5
    end=$6
else
    Mconst=128
    Nconst=128
    Kconst=128
    start=8
    step=8
    end=8192
    if [ $# -ne 0 ] 
    then
        echo "Wrong number of arguments!"
    fi
fi

echo "const M="$Mconst "N="$Nconst "K="$Kconst
echo "start="$start "step="$step "end="$end

> 'results_M.csv'
> 'results_N.csv'
> 'results_K.csv'

for (( i=$start; i<=$end; i+=$step ))
do
    echo $i","$(./a.out --increment $i $Nconst $Kconst) >> 'results_M.csv'
done

for (( i=$start; i<=$end; i+=$step ))
do
    echo $i","$(./a.out --increment $Mconst $i $Kconst) >> 'results_N.csv'
done

for (( i=$start; i<=$end; i+=$step ))
do
    echo $i","$(./a.out --increment $Mconst $Nconst $i) >> 'results_K.csv'
done

gnuplot -c gnuplot_commands.plt $end $(($end/32))