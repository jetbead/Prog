#!/usr/bin/perl
use strict;
use warnings;
use Encode;
use utf8;
use Data::Dumper;

binmode STDIN, ":utf8";
binmode STDERR, ":utf8";
binmode STDOUT, ":utf8";

my %hash = (
    "computer", 0,
    "domestic", 1,
    "economy", 2,
    "entertainment", 3,
    "local", 4,
    "science", 5,
    "sports", 6,
    "world", 7
    );

while(<>){
    chomp;

    my $line = $_;
    my @sp = split(/ /, $line);
    my $n = scalar(@sp);
    
    print $hash{$sp[$n-1]}," ";
    for(my $i=0; $i<$n-1; $i++){
        print $sp[$i];
        if($i != $n-2){
            print " ";
        }
    }
    print "\n";
}

