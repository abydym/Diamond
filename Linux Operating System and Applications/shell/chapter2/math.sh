#!/bin/bash
# math.sh - 输入两个整数，输出加减乘除结果

read -p "请输入两个非零整数 (用空格隔开): " x y

# 进行运算
# 注意：Shell默认只支持整数运算，除法会直接取整（例如 5/2=2）
echo "$x + $y = $((x + y))"
echo "$x - $y = $((x - y))"
echo "$x * $y = $((x * y))"
echo "$x / $y = $((x / y))"
