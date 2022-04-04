#set multiplot layout 2,2 rowsfirst
set xtics 0,256,8192
set ytics 0,5,100
set grid
set datafile separator ","
plot "results_M.csv" using 1:2 with lines lt rgb "red" title "Performance(M)", \
     "results_N.csv" using 1:2 with lines lt rgb "#009900" title "Performance(N)", \
     "results_K.csv" using 1:2 with lines lt rgb "blue" title "Performance(K)"
pause -1