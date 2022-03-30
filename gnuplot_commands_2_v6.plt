#set multiplot layout 2,2 rowsfirst
set xtics 0,256,8192
plot "./MatrMulV6/results_M_2_v6.csv" with lines, \
     "./MatrMulV6/results_N_2_v6.csv" with lines lt rgb "#007700", \
     "./MatrMulV6/results_K_2_v6.csv" with lines lt rgb "blue" #smooth csplines
pause -1