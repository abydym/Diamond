#!/bin/bash
# 题目要求：计算 1+1/2+1/3+...+1/n
# 注意：Shell 默认不支持浮点运算，这里使用 awk 实现

read -p "请输入 n 的值: " n

# 使用 awk 进行浮点数累加
result=$(awk -v num="$n" 'BEGIN {
    sum = 0;
    for (i = 1; i <= num; i++) {
        sum += 1/i;
    }
    print sum;
}')

echo "1+1/2+...+1/$n 的结果是: $result"
