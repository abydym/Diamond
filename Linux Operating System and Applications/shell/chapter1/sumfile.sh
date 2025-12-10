#!/bin/bash
# sumfile.sh - 统计 /etc, /var, /usr 的一级子目录和文件总数

# 统计 /etc
count_etc=$(ls -1 /etc | wc -l)

# 统计 /var
count_var=$(ls -1 /var | wc -l)

# 统计 /usr
count_usr=$(ls -1 /usr | wc -l)

# 计算总和
total=$((count_etc + count_var + count_usr))

echo "---------------------------------"
echo "/etc 目录下的项目数: $count_etc"
echo "/var 目录下的项目数: $count_var"
echo "/usr 目录下的项目数: $count_usr"
echo "---------------------------------"
echo "三个目录总共包含: $total 个一级子目录和文件"
