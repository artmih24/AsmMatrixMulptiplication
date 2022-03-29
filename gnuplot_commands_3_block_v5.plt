#set multiplot layout 2,2 rowsfirst
#set xtics 0,64,512
#set ytics 0,64,512
splot "./MatrMulV5Block/results2_M_N_block_v5.csv" matrix columnheaders rowheaders with lines, \
      "./MatrMulV5Block/results2_N_K_block_v5.csv" matrix columnheaders rowheaders with lines lt rgb "#007700", \
      "./MatrMulV5Block/results2_M_K_block_v5.csv" matrix columnheaders rowheaders with lines lt rgb "blue" #smooth csplines
pause -1