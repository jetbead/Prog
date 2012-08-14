#!/bin/zsh

perl svm_fobos.pl a9a.txt 0.1 0.00001 < a9a.t
perl svm_fobos.pl a9a.txt 0.1 0.00005 < a9a.t
perl svm_fobos.pl a9a.txt 0.1 0.0001 < a9a.t
perl svm_fobos.pl a9a.txt 0.1 0.0005 < a9a.t
perl svm_fobos.pl a9a.txt 0.1 0.001 < a9a.t
perl svm_fobos.pl a9a.txt 0.1 0.005 < a9a.t
perl svm_fobos.pl a9a.txt 0.1 0.01 < a9a.t

perl svm_fobos.pl a9a.txt 0.01 0.00001 < a9a.t
perl svm_fobos.pl a9a.txt 0.01 0.00005 < a9a.t
perl svm_fobos.pl a9a.txt 0.01 0.0001 < a9a.t
perl svm_fobos.pl a9a.txt 0.01 0.0005 < a9a.t
perl svm_fobos.pl a9a.txt 0.01 0.001 < a9a.t
perl svm_fobos.pl a9a.txt 0.01 0.005 < a9a.t

perl svm_fobos.pl a9a.txt 0.001 0.00001 < a9a.t
perl svm_fobos.pl a9a.txt 0.001 0.00005 < a9a.t
perl svm_fobos.pl a9a.txt 0.001 0.0001 < a9a.t
perl svm_fobos.pl a9a.txt 0.001 0.0005 < a9a.t

