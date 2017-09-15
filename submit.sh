#!/bin/bash

for i in 1 2 4 8 16
do
    qsub -pe single $i -l h_rt=0:30:00,mem=1G -q \*@@elves run-all.sh
done
