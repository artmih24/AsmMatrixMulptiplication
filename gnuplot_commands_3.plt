splot "results_3_M_N.csv" matrix columnheaders rowheaders with lines lt rgb "red" title "Performance(M-N)", \
      "results_3_M_K.csv" matrix columnheaders rowheaders with lines lt rgb "#009900" title "Performance(M-K)", \
      "results_3_N_K.csv" matrix columnheaders rowheaders with lines lt rgb "blue" title "Performance(N-K)"
pause -1