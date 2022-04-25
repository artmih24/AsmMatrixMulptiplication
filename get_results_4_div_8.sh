#!/bin/bash -e

#./compile.sh

if [ $# -eq 1 ]; then
    if [ $1 -ge 4096 ]; then
        Mconst=128; Nconst=128; Kconst=128; start=8; step=8; end=$1
    else
        Mconst=$1; Nconst=$1; Kconst=$1; start=8; step=8; end=4096
    fi
elif [ $# -eq 2 ]; then
    if [ $2 -ge 64 ]; then
        Mconst=$1; Nconst=$1; Kconst=$1; start=8; step=8; end=$2
    else
        Mconst=$1; Nconst=$1; Kconst=$1; start=$2; step=$2; end=4096
    fi
elif [ $# -eq 3 ]; then
    if [ $3 -ge 4096 ]; then
        Mconst=$1; Nconst=$1; Kconst=$1; start=$2; step=$2; end=$3
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=8; step=8; end=4096
    fi
elif [ $# -eq 4 ]; then
    if [ $4 -ge 64 ]; then
        Mconst=$1; Nconst=$2; Kconst=$3; start=8; step=8; end=$4
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$4; end=4096
    fi
elif [ $# -eq 5 ]; then
    if [ $5 -ge 64 ]; then
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$4; end=$5
    else
        Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$5; end=4096
    fi
elif [ $# -eq 6 ]; then
    Mconst=$1; Nconst=$2; Kconst=$3; start=$4; step=$5; end=$6
else
    Mconst=128; Nconst=128; Kconst=128; start=8; step=8; end=4096
    echo "Default values"
    if [ $# -ne 0 ]; then
        echo "Wrong number of arguments!"
    fi
fi

N=1

echo "---- Bash script ----"
echo "const M = "$Mconst", N = "$Nconst", K = "$Kconst
echo "start = "$start", step = "$step", end = "$end
echo "launched at "$(date +"%T")

echo "M/N/K,Performance(M),Performance(N),Performance(K),Performance(M)max,Performance(N)max,Performance(K)max" > 'results_4_div_8.csv'

startTime=$(date +%s)

for (( i=$start; i<=$end; i+=$step )); do
    PerformanceM=0
    PerformanceN=0
    PerformanceK=0
    PerformanceMmax=0
    PerformanceNmax=0
    PerformanceKmax=0
    for (( j=0; j<$N; j+=1 )); do
        PerformanceMj=$(./a.out --increment $i $Nconst $Kconst)
        if [[ $PerformanceMj != "" ]]; then
            PerformanceM=$(bc <<< "scale=6; $PerformanceM + $PerformanceMj")
            if (($(bc <<< "scale=6; $PerformanceMj > $PerformanceMmax"))); then
                PerformanceMmax=$PerformanceMj
            fi
        fi
    done
    for (( j=0; j<$N; j+=1 )); do
        PerformanceNj=$(./a.out --increment $Mconst $i $Kconst)
        if [[ $PerformanceNj != "" ]]; then
            PerformanceN=$(bc <<< "scale=6; $PerformanceN + $PerformanceNj")
            if (($(bc <<< "scale=6; $PerformanceNj > $PerformanceNmax"))); then
                PerformanceNmax=$PerformanceNj
            fi
        fi
    done
    for (( j=0; j<$N; j+=1 )); do
        PerformanceKj=$(./a.out --increment $Mconst $Nconst $i)
        if [[ $PerformanceKj != "" ]]; then
            PerformanceK=$(bc <<< "scale=6; $PerformanceK + $PerformanceKj")
            if (($(bc <<< "scale=6; $PerformanceKj > $PerformanceKmax"))); then
                PerformanceKmax=$PerformanceKj
            fi
        fi
    done
    PerformanceM=$(bc <<< "scale=6; ($PerformanceM / $N) / 8")
    PerformanceN=$(bc <<< "scale=6; ($PerformanceN / $N) / 8")
    PerformanceK=$(bc <<< "scale=6; ($PerformanceK / $N) / 8")
    PerformanceMmax=$(bc <<< "scale=6; $PerformanceMmax / 8")
    PerformanceNmax=$(bc <<< "scale=6; $PerformanceNmax / 8")
    PerformanceKmax=$(bc <<< "scale=6; $PerformanceKmax / 8")
    if (($(bc <<< "scale=6; $PerformanceM < 1"))); then
        PerformanceM="0"$PerformanceM
    fi
    if (($(bc <<< "scale=6; $PerformanceN < 1"))); then
        PerformanceN="0"$PerformanceN
    fi
    if (($(bc <<< "scale=6; $PerformanceK < 1"))); then
        PerformanceK="0"$PerformanceK
    fi
    if (($(bc <<< "scale=6; $PerformanceMmax < 1"))); then
        PerformanceMmax="0"$PerformanceMmax
    fi
    if (($(bc <<< "scale=6; $PerformanceNmax < 1"))); then
        PerformanceNmax="0"$PerformanceNmax
    fi
    if (($(bc <<< "scale=6; $PerformanceKmax < 1"))); then
        PerformanceKmax="0"$PerformanceKmax
    fi
    if (($(bc <<< "scale=6; $PerformanceM == 0"))); then
        PerformanceM=""
    fi
    if (($(bc <<< "scale=6; $PerformanceN == 0"))); then
        PerformanceN=""
    fi
    if (($(bc <<< "scale=6; $PerformanceK == 0"))); then
        PerformanceK=""
    fi
    if (($(bc <<< "scale=6; $PerformanceMmax == 0"))); then
        PerformanceMmax=""
    fi
    if (($(bc <<< "scale=6; $PerformanceNmax == 0"))); then
        PerformanceNmax=""
    fi
    if (($(bc <<< "scale=6; $PerformanceKmax == 0"))); then
        PerformanceKmax=""
    fi
    echo $i","$PerformanceM","$PerformanceN","$PerformanceK","$PerformanceMmax","$PerformanceNmax","$PerformanceKmax  >> 'results_4_div_8.csv'
done

endTime=$(date +%s)
timeDiffSeconds=$(($endTime - $startTime))
timeDiffMinutes=$(($timeDiffSeconds / 60))
if [ $timeDiffMinutes -gt 0 ]; then
    timeDiffSeconds=$(($timeDiffSeconds % 60))
    if [ $timeDiffSeconds -lt 10 ]; then
        timeDiffSeconds="0"$timeDiffSeconds
    fi
    echo "time spent: "$timeDiffMinutes" m "$timeDiffSeconds" s"
else
    echo "time spent: "$timeDiffSeconds" s"
fi

gnuplot -c gnuplot_commands_4_div_8.plt $end $(($end/32)) $start $N