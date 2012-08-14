set terminal png
set output "out.png"
set yrange [0:900]

set key bottom
plot "out" using 1:2 w lp t "predict_data", "" using 1:3 w lp t "train_data"