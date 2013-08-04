#!/usr/bin/perl
use strict;
use warnings;

my $file = shift;
my %df;

open(IN, "<", $file) or die "cannot open file:$!";

while(<IN>){
    chomp;

    my @sp = split(/ /);
    for(my $i=1; $i<@sp; $i++){
        my @ss = split(/:/, $sp[$i]);
        if(exists $df{$ss[0]}){
            $df{$ss[0]}++;
        }else{
            $df{$ss[0]} = 1;
        }
    }
}

my $docn = keys %df;

while(<>){
    chomp;

    my @sp = split(/ /);
    print $sp[0]," ";
    my $termn = 0;
    for(my $i=1; $i<@sp; $i++){
        my @ss = split(/:/, $sp[$i]);
        $termn += $ss[1];
    }
    for(my $i=1; $i<@sp; $i++){
        my @ss = split(/:/, $sp[$i]);
        if(!exists $df{$ss[0]}){
            $df{$ss[0]} = 0;
        }
        print $ss[0],":",( ($ss[1]/$termn)*log($docn/($df{$ss[0]}+1)) );
        if($i != @sp-1){
            print " ";
        }
    }
    print "\n";
}
