#! /usr/bin/perl
use strict;
use warnings;

## 学習パート
#  暖色なら1、寒色なら-1の正解ラベル
my @x_list = (
    {R => 255, G =>   0, B =>   0, bias => 1},
    {R =>   0, G => 255, B => 255, bias => 1},
    {R =>   0, G => 255, B =>   0, bias => 1},
    {R => 255, G =>   0, B => 255, bias => 1},
    {R =>   0, G =>   0, B => 255, bias => 1},
    {R => 255, G => 255, B =>   0, bias => 1},
    );
my @t_list = (1,-1,-1,1,-1,1); #正解データ

## 訓練パート
my $w = {R => 0, G => 0, B => 0, bias => 1};
my $loop = 10;
while($loop--){
    for(my $i = 0; $i < @x_list; $i++){
	train($w, $x_list[$i], $t_list[$i]);
    }
}

## 推定パート
while(<>){
    chomp;
    my @fs = split(/ /);
    if(@fs != 3){
	warn "invalid input data.\n";
	next;
    }
    
    my $x = {R => $fs[0], G => $fs[1], B => $fs[2], bias => 1};
    my $t = predict($w, $x);
    if($t >= 0){
	print "> warm color.\n";
    }else{
	print "> cold color.\n";
    }
}

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

#損失関数
sub loss {
    my $w = shift;
    my $x = shift;
    my $t = shift;

    my $y = 0;
    foreach my $f (keys %$x){
	if($w->{$f}){
	    $y += ($w->{$f} * $x->{$f});
	}
    }
    return 0.0 if($t*$y >= 1);
    return 1.0 - $t*$y;
}

#学習
sub train {
    my $w = shift;
    my $x = shift;
    my $t = shift;
    
    my $l = loss($w, $x, $t);
    my $sq_x = 0.0;
    foreach my $f (keys %$x){
	$sq_x += ($x->{$f} * $x->{$f});
    }
    my $tau = $l / $sq_x;
    if($l > 0){
	foreach my $f(keys %$x){
	    $w->{$f} += $tau * ($t * $x->{$f});
	}
    }
}
