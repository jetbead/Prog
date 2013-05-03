set terminal png size 500,500

set output "sig.png"
set xrange [0:1024]
plot "signal.txt" w l

set xrange [0:1024]
set output "sig_denoise.png"
plot "denoise.txt" w l