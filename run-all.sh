#!/bin/bash
#$ -l mem=512M
#$ -l h_rt=0:10:00
#$ -cwd
#$ -j y
##$ -m abe
##$ -M kevin.dice1@gmail.com

for x in {1..200}
do
    /homes/kmdice/625/hw2/pthreads $NSLOTS
done;
