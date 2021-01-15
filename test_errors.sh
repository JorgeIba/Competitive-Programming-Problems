#!/bin/bash
zero=0

for i in {2..100};
do
    for j in {2..100};
    do
        if [[ $i -ne $j ]];
        then
            expr="$i $j"
            echo $expr > test.txt
            mine_out=$(./mine.exe < test.txt)
            ac_out=$(./ac.exe < test.txt)

            if [ $mine_out != $ac_out ];
            then
                echo $mine_out $expr
            fi
        fi
    done
    echo $i
done
