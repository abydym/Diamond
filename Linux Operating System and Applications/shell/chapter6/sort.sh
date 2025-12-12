#!/bin/bash
# sort.sh - 输入三个数升序输出

echo "请输入三个数 (用空格隔开):"
read a b c

echo "升序排序结果:"
# echo -e 将三个数分行输出，然后通过管道 | 传给 sort 命令
# sort -n 表示按“数值”大小排序 (numeric)，而不是按字符排序
echo -e "$a\n$b\n$c" | sort -n
