#!/usr/bin/perl
use strict;
use warnings;

while(<>){
    chomp;

    my @sp = split(/ /);
    print $sp[0]," ";
    for(my $i=1; $i<@sp; $i++){
        my @ss = split(/:/, $sp[$i]);
        print $ss[0],":1";
        if($i != @sp-1){
            print " ";
        }
    }
    print "\n";
}
