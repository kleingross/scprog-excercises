reset
set term gif animate size 800,600
set output "gravity.gif"
set xrange [-1e9:1e9]
set yrange [-1e9:1e9]
set style line 1 linecolor rgb "black" linewidth 2 pointtype 7 pointsize 2
set nokey
n=500
i=0
load "plot_gravity.plt"
set output