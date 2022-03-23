#set multiplot layout 2,2 rowsfirst
set xtics 0,256,8192
plot "results_M.csv" with lines, \
     "results_N.csv" with lines lt rgb "#007700", \
     "results_K.csv" with lines lt rgb "blue" #smooth csplines
pause -1