#!/usr/bin/perl
use strict;
use warnings;
use Encode;
use utf8;
use Data::Dumper;

binmode STDIN, ":utf8";
binmode STDERR, ":utf8";
binmode STDOUT, ":utf8";

sub func {
    my ($n, $str) = @_;

    my @chs = split(//, $str);

    print 2*$n,"\t";

    for(my $i=0; $i<@chs-1; $i++){
        if($chs[$i] eq '日' && $chs[$i+1] eq '本'){
            
            for(my $j=0; $j<$n; $j++){
                if($i-$n+$j >= 0){
                    print $chs[$i-$n+$j];
                }else{
                    print "\$";
                }
                if($j != $n-1){
                    print " ";
                }
            }
            print " ";
            for(my $k=0; $k<$n; $k++){
                if($i+2+$k < @chs){
                    print $chs[$i+2+$k];
                }else{
                    print "\$";
                }
                if($k != $n-1){
                    print " ";
                }
            }
            last;
        }
    }
}


while(<>){
    chomp;
    
    my @sp = split(/\t/, $_);
    
    print $sp[0],"\t";
    func(5, $sp[1]);
    print "\n";
}
