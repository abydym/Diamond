#!/bin/bash
# 题目要求：用 for 语句完成求和

total=0
# 使用 {1..100} 生成序列
for i in {1..100}
do
    total=$((total + i))
done

echo "The result (For) is $total"
