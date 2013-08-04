#!/usr/bin/perl
use strict;
use warnings;

while(<>){
    chomp;

    my @sp = split(/ /);
    print $sp[0]," ";
    my $vsize = 0;
    for(my $i=1; $i<@sp; $i++){
        my @ss = split(/:/, $sp[$i]);
        $vsize += ($ss[1] * $ss[1]);
    }
    $vsize = sqrt($vsize);

    for(my $i=1; $i<@sp; $i++){
        my @ss = split(/:/, $sp[$i]);
        print $ss[0],":",($ss[1]/$vsize);
        if($i != @sp-1){
            print " ";
        }
    }
    print "\n";
}
