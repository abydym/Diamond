#!/bin/bash

# 确保文件 math.txt 存在并清空，以便每次运行时都有一个干净的开始
# 这一步不是必需的，但能让结果更清晰
> math.txt 

# --- 任务一：使用 let 计算 2*3*4*5 ---
# let 命令用于执行 Shell 内部的算术运算，它比 expr 更快，因为它不需要派生新的进程。
# 结果会直接追加到 math.txt 文件中。
echo "--- 任务一: let 计算 2*3*4*5 ---" >> math.txt
let "result1 = 2 * 3 * 4 * 5"
echo "计算结果: $result1" >> math.txt
echo "===================================" >> math.txt

# --- 任务二：使用 expr 计算 4 的立方 (4*4*4) ---
# expr 命令用于求表达式的值。注意：在 expr 中，乘号 * 必须用反斜杠 \ 进行转义，
# 否则 Shell 会把它当做通配符。
echo "--- 任务二: expr 计算 4 的立方 ---" >> math.txt
# `expr 4 \* 4 \* 4` 计算 4^3
result2=$(expr 4 \* 4 \* 4)
echo "计算结果: $result2" >> math.txt
echo "===================================" >> math.txt

# --- 任务三：使用 bc 将二进制 1001011 转换为十进制 ---
# bc 是一个任意精度的计算器语言，它非常适合进行进制转换。
# ibase=N 设置输入基数（Input Base）为 N。
# obase=M 设置输出基数（Output Base）为 M。
echo "--- 任务三: bc 进制转换 (二进制 1001011 -> 十进制) ---" >> math.txt
# 设置输入基数为 2，然后直接输入要转换的二进制数
result3=$(echo "ibase=2; 1001011" | bc)
echo "计算结果: $result3" >> math.txt
echo "===================================" >> math.txt

# 脚本执行完毕，显示 math.txt 的内容以供检查
echo -e "\n--- 所有任务已完成，这是 math.txt 的内容：---\n"
cat math.txt
