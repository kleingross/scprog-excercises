reset
set term gif animate size 512,512
set output "disk.gif"
set xrange [0:1000]
set yrange [0:1000]
set nokey
n=500
i=0
load "plot_disk.plt"
set output