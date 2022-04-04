#set multiplot layout 2,2 rowsfirst
set xtics 0,2048,65536
plot "./MatrMulV6/results2_M_2_v6_65536.csv" with lines, \
     "./MatrMulV6/results2_N_2_v6_65536.csv" with lines lt rgb "#007700", \
     "./MatrMulV6/results2_K_2_v6_65536.csv" with lines lt rgb "blue" #smooth csplines
pause -1