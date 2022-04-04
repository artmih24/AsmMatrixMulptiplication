#!/usr/local/bin/gnuplot --persist

#set multiplot layout 2,2 rowsfirst
end=ARG1
step=ARG2
if (!exists(ARG1)) end=8192
if (!exists(ARG2)) step=256
#print end
set xtics 0,step,end
set ytics 0,5,100
set grid
set datafile separator ","
plot "results_M.csv" using 1:2 with lines lt rgb "red" title "Performance(M)", \
     "results_N.csv" using 1:2 with lines lt rgb "#009900" title "Performance(N)", \
     "results_K.csv" using 1:2 with lines lt rgb "blue" title "Performance(K)"
pause -1