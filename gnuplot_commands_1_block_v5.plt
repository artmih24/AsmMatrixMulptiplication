#set multiplot layout 2,2 rowsfirst
set xtics 0,256,8192
plot "results_M_1_block_v5.csv" with lines, \
     "results_N_1_block_v5.csv" with lines lt rgb "#007700", \
     "results_K_1_block_v5.csv" with lines lt rgb "blue" #smooth csplines
pause -1