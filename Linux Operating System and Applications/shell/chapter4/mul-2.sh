#!/bin/bash
# 只使用 while 循环实现 99 乘法表
echo "--- While 循环乘法表 ---"
i=1
while [ $i -le 9 ]
do
    j=1
    while [ $j -le $i ]
    do
        echo -n -e "$j*$i=$((i*j))\t"
        let j++
    done
    echo "" # 换行
    let i++
done
