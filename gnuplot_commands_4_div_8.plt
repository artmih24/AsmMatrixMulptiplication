#!/usr/local/bin/gnuplot --persist

#set multiplot layout 2,2 rowsfirst
print "---- Gnuplot script ----"
end = ARG1
step = ARG2
start = ARG3
n = ARG4
if (start eq "") {
     start = 0
     print "default start = ", start
}
else {
     print "start = ", start
}
if (step eq "") {
     step = 256
     print "default step = ", step
}
else {
     if (step % 8 != 0) {
          step = step * 2
     }
     print "step = ", step
}
if (end eq "") {
     end = 8192
     print "default end = ", end
}
else {
     print "end = ", end
}
if (n eq "") {
     n = 1
}
set xtics 0,step,end
set ytics 0,5,100
set xrange [start:end]
#set yrange [0:100]
set grid
set datafile separator ","
if (n == 1) {
     plot "results_4_div_8.csv" using 1:2 with lines linetype rgb "red" title columnhead, \
          "results_4_div_8.csv" using 1:3 with lines linetype rgb "#009900" title columnhead, \
          "results_4_div_8.csv" using 1:4 with lines linetype rgb "blue" title columnhead
}
else {
     plot "results_4_div_8.csv" using 1:2 with lines linetype rgb "red" title columnhead, \
          "results_4_div_8.csv" using 1:3 with lines linetype rgb "#009900" title columnhead, \
          "results_4_div_8.csv" using 1:4 with lines linetype rgb "blue" title columnhead, \
          "results_4_div_8.csv" using 1:5 with lines linetype rgb "red" dt 2 title columnhead, \
          "results_4_div_8.csv" using 1:6 with lines linetype rgb "#009900" dt 2 title columnhead, \
          "results_4_div_8.csv" using 1:7 with lines linetype rgb "blue" dt 2 title columnhead
}
pause -1