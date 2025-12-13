#!/bin/bash
# 题目要求：调试程序，理解变量含义
# $0: 当前脚本的文件名
# $#: 传递给脚本的参数总个数
# $@: 传递给脚本的所有参数列表
# $1-$9: 第1到第9个参数

echo "program name: $0"
echo "all parameters: $@"
echo "first three parameters: $1 $2 $3"

echo "--- 执行 shift (左移1位) ---"
shift
echo "program name: $0"
echo "all parameters: $@"
echo "first three parameters: $1 $2 $3"

echo "--- 执行 shift 3 (左移3位) ---"
shift 3
echo "program name: $0"
echo "all parameters: $@"
echo "first three parameters: $1 $2 $3"
exit 0
