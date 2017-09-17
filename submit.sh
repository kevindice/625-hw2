#!/bin/bash

for i in 1 2 4 8 16
do
    qsub -pe single $i -q \*@@elves run-all.sh
done
