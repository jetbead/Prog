#! /usr/bin/perl
# Usage : perl svm_fobos.pl train_file param_eta param_lambda_hat < test_file
use strict;
use warnings;

#学習ファイル名
my $train_file = shift;
#パラメータ
my $param_eta = shift;
my $param_lambda_hat = shift;

print $param_eta," ",$param_lambda_hat,"\n";

#訓練回数(学習データの個数*$loop個の学習を行う)
my $loop = 10;

#重みベクトル
my $w = {};

## 学習データの読み込み
my @x_list;
my @t_list;
open IN, $train_file;
while(<IN>){
    chomp;
    my @list = split(/\s+/, $_);
    push(@t_list, $list[0]);
    my $hash;
    for(my $i=1; $i<@list; $i++){
	my ($a, $b) = split(/:/,$list[$i]);
	$hash->{$a} = $b;
	$w->{$a} = 0;
    }
    push(@x_list, $hash);
}

## 訓練
$|=1; #printのオートフラッシュ有効
print "training";
while($loop--){
    print ".";
    for(my $i = 0; $i < @x_list; $i++){
	train($w, $x_list[$i], $t_list[$i], $param_eta, $param_lambda_hat);
    }
}
print "finish!\n";

## 推定
my $num = 0;
my $success = 0;
while(<>){
    chomp;
    my @list = split(/\s+/, $_);
    my $hash;
    for(my $i=1; $i<@list; $i++){
	my ($a, $b) = split(/:/,$list[$i]);
	$hash->{$a} = $b;
    }

    my $t = predict($w, $hash);
    $num++;
    if($t * $list[0] > 0){
	$success++;
    }
}

## 結果の出力
print "Result : ",($success/$num)," (",$success,"/",$num,")\n";

#重みが0の要素の割合
my $elem_num = 0;
my $zero_num = 0;
foreach my $f(keys %$w){
    $elem_num++;
    print $f,"\t",$w->{$f},"\n";
    if($w->{$f} == 0){
	$zero_num++;
    }
}
print "Zero element : ",($zero_num/$elem_num)," (",$zero_num,"/",$elem_num,")\n";

##################################################
#予測
sub predict {
    my $w = shift;
    my $x = shift;
    
    my $y = 0;
    foreach my $f (keys %$x){
	if($w->{$f}){
	    $y += ($w->{$f} * $x->{$f});
	}
    }
    return $y;
}

#学習
sub train {
    my $w = shift;
    my $x = shift;
    my $t = shift;
    my $eta = shift;
    my $lambda_hat = shift;

    #損失による勾配
    my $y = predict($w, $x);
    if($y*$t < 1){
	foreach my $f(keys %$x){
	    $w->{$f} += $eta * $t * $x->{$f};
	}

	
	#正則化
	foreach my $f(keys %$w){
	    if($w->{$f} > 0){
		if($w->{$f} - $lambda_hat > 0){
		    $w->{$f} -= $lambda_hat;
		}else{
		    $w->{$f} = 0;
		}
	    }else{
		if($w->{$f} + $lambda_hat > 0){
		    $w->{$f} = 0;
		}else{
		    $w->{$f} += $lambda_hat;
		}
	    }
	}
    }
}
