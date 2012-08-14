set terminal png
set output "out2.png"

set key bottom
plot "sin_curve.out" using 1:2 w lp t "predict_data", "" using 1:3 w lp t "train_data"