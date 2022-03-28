#set multiplot layout 2,2 rowsfirst
set xtics 0,2048,65536
plot "./MatrMulV5Block/results_M_2_block_v5.csv" with lines, \
     "./MatrMulV5Block/results_N_2_block_v5.csv" with lines lt rgb "#007700", \
     "./MatrMulV5Block/results_K_2_block_v5.csv" with lines lt rgb "blue" #smooth csplines
pause -1