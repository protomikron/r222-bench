#!/bin/bash
(( $# < 1 )) && echo "usage: $0 lang0 [... <langN>]" && exit 1

langs=$@
db=db.txt

for lang in $langs; do
    for run in {0..4}; do
        rm -f $db

        start=$(date +%s.%N)
        ./$lang >$db;
        stop=$(date +%s.%N)

        elapsed_s=$(echo "$stop - $start" | bc)
        echo "running $lang [$run] took $elapsed_s seconds"
    done
done

