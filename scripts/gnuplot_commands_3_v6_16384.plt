#set multiplot layout 2,2 rowsfirst
set xtics 0,512,16384
plot "./MatrMulV6/results3_M_v6_16384.csv" with lines lt rgb "red", \
     "./MatrMulV6/results3_N_v6_16384.csv" with lines lt rgb "#007700", \
     "./MatrMulV6/results3_K_v6_16384.csv" with lines lt rgb "blue" #smooth csplines
pause -1