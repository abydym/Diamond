#!/bin/bash
# 输出数字等边三角形
# 规律：第 i 行，打印数字 i，打印次数为 2*i - 1，前方空格数为 总行数-i

# 默认边长为3，也可以让用户输入
read -p "请输入三角形边长 (默认3): " n
if [ -z "$n" ]; then n=3; fi

for ((i=1; i<=n; i++))
do
    # 1. 打印前导空格 (为了让三角形居中)
    for ((s=n-i; s>0; s--)); do
        echo -n " "
    done

    # 2. 打印数字
    # 计算该行需要打印多少个数字 (2*i - 1)
    count=$((2*i - 1))
    for ((k=1; k<=count; k++)); do
        echo -n "$i"
    done

    # 3. 换行
    echo ""
done
