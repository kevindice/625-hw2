#!/bin/bash
#$ -l mem=512M
#$ -l h_rt=0:10:00
#$ -t 1-20
#$ -cwd
#$ -j y
##$ -m abe
##$ -M kevin.dice1@gmail.com

for x in {1..50}
do
    /homes/kmdice/625/hw2/pthreads $NSLOTS
done;

for x in {1..50}
do
    /homes/kmdice/625/hw2/openmp $NSLOTS
done;
