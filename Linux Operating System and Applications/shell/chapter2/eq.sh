#!/bin/bash
# eq.sh - 判断两个整数是否相等

read -p "请输入两个非零整数 (用空格隔开): " x y

if [ "$x" -eq "$y" ]; then
    echo "YES"
else
    echo "NO"
fi
