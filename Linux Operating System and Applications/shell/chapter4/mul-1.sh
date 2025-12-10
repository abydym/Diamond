#!/bin/bash
# 只使用 for 循环实现 99 乘法表
echo "--- For 循环乘法表 ---"
for ((i=1; i<=9; i++))
do
    for ((j=1; j<=i; j++))
    do
        # -n 不换行, \t 制表符对齐
        echo -n -e "$j*$i=$((i*j))\t"
    done
    echo "" # 换行
done
