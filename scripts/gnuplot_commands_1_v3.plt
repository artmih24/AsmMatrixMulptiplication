#set multiplot layout 2,2 rowsfirst
set xtics 0,512,16384
plot "results_M_1_v3.csv" with lines, \
     "results_N_1_v3.csv" with lines lt rgb "#007700", \
     "results_K_1_v3.csv" with lines lt rgb "blue" #smooth csplines
pause -1