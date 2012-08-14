#! /usr/bin/perl
# Usage : perl PA-II.pl train_file parameter_C < test_file
use strict;
use warnings;

#学習ファイル名
my $train_file = shift;
#パラメータ
my $C = shift;

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
while($loop--){
    for(my $i = 0; $i < @x_list; $i++){
	train($w, $x_list[$i], $t_list[$i]);
    }
}

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
    if($t * $list[0] >= 0){
	$success++;
    }
}

## 結果の出力
print "Result : ",($success/$num)," (",$success,"/",$num,")\n";

##################################################
#予測
sub predict {
    my ($w, $x) = @_;
    
    my $y = 0;
    foreach my $f (keys %$x){
	if($w->{$f}){
	    $y += ($w->{$f} * $x->{$f});
	}
    }
    return $y;
}

#損失関数
sub loss {
    my ($w, $x, $t) = @_;

    my $y = 0;
    foreach my $f (keys %$x){
	if($w->{$f}){
	    $y += ($w->{$f} * $x->{$f});
	}
    }
    return 0.0 if(1.0 - $t*$y <= 0);
    return 1.0 - $t*$y;
}

#学習
sub train {
    my ($w, $x, $t) = @_;
    
    my $l = loss($w, $x, $t);
    my $sq_x = 0.0;
    foreach my $f (keys %$x){
	$sq_x += ($x->{$f} * $x->{$f});
    }

    ## PA
    #my $tau = $l / $sq_x;

    ## PA-I
    #my $tau = $l / $sq_x;
    #$tau = $C if($tau > $C);

    ## PA-II
    my $tau = $l / ($sq_x + 1.0 / (2 * $C));

    # 更新
    foreach my $f(keys %$x){
	$w->{$f} += $tau * ($t * $x->{$f});
    }
}
