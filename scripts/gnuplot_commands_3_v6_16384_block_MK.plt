#set multiplot layout 2,2 rowsfirst
set xtics 0,512,16384
plot "./MatrMulV6/blockMK/results3_M_v6_16384_block.csv" with lines lt rgb "red", \
     "./MatrMulV6/blockMK/results3_N_v6_16384_block.csv" with lines lt rgb "#009900", \
     "./MatrMulV6/blockMK/results3_K_v6_16384_block.csv" with lines lt rgb "blue" #smooth csplines
pause -1