#set multiplot layout 2,2 rowsfirst
set xtics 0,2048,65536
plot "./MatrMulV6/results3_M_v6_65536_block.csv" with lines lt rgb "red", \
     "./MatrMulV6/results3_N_v6_65536_block.csv" with lines lt rgb "#009900", \
     "./MatrMulV6/results3_K_v6_65536_block.csv" with lines lt rgb "blue" #smooth csplines
pause -1