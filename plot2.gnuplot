#!/usr/bin/env gnuplot

set term pngcairo size 730, 550;
set output "out2.png"
set datafile separator ";";

set title "Execution times"
set xlabel "Condition probability"
set ylabel "Compute time [s]"

set xrange [0:1]
set yrange [0:]

plot \
    "out.csv" using 1:6 with lines title "time_branch_mem_with_use", \
    "out.csv" using 1:7 with lines title "time_cmov_mem_with_use"

#    1 + 16*x*(1-x) with lines linewidth 3 linetype 0
