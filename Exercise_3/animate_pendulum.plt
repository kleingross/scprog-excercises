reset
set term gif animate size 800,600
set output "pendulum.gif"
set xrange [-4:4]
set yrange [-9:1]
set style line 1 linecolor rgb "black" linewidth 2 pointtype 7 pointsize 2
set nokey
n=500
i=0
load "plot_pendulum.plt"
set output