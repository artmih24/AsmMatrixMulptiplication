#!/usr/local/bin/gnuplot --persist

#set multiplot layout 2,2 rowsfirst
end = ARG1
step = ARG2
if (end eq "") {
     end = 8192
     print "default end = ", end
}
else {
     print "end = ", end
}
if (step eq "") {
     step = 256
     print "default step = ", step
}
else {
     print "step = ", step
}
set xtics 0,step,end
set ytics 0,5,100
set yrange [0:100]
set grid
set datafile separator ","
plot "results_N_const.csv" using 1:2 with lines lt rgb "#009900" title "Performance(M, K)"
pause -1