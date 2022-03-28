#set multiplot layout 2,2 rowsfirst
set xtics 0,2560,81920
plot "results_M_1_big.csv" with lines smooth csplines, \
     "results_N_1_big.csv" with lines lt rgb "#007700" smooth csplines, \
     "results_K_1_big.csv" with lines lt rgb "blue" smooth csplines
pause -1