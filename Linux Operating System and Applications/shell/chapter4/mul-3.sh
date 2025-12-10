#!/bin/bash
# 外层用 for，内层用 while
echo "--- For + While 混合乘法表 ---"
for ((i=1; i<=9; i++))
do
    j=1
    while [ $j -le $i ]
    do
        echo -n -e "$j*$i=$((i*j))\t"
        let j++
    done
    echo ""
done
