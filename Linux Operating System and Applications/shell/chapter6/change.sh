#!/bin/bash
# change.sh - 小写转大写

read -p "请输入一个字符串: " str

# 使用 tr 命令进行转换
# 'a-z' 代表所有小写，'A-Z' 代表所有大写
result=$(echo "$str" | tr 'a-z' 'A-Z')

echo "转换后的结果: $result"

# 补充知识：Bash 4.0+ 也可以用 echo "${str^^}" 这种写法
