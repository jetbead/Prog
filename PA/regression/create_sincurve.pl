#!/usr/bin/perl
use strict;
use warnings;


my $n = 100;

for(my $i=0; $i<$n; $i++){
    print sin($i * 0.1)," 1:",$i,"\n";
}
