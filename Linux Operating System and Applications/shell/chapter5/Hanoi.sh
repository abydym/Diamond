#!/bin/bash
# Hanoi.sh - 汉诺塔移动步骤

# 定义移动函数
# 参数含义: $1:盘子数, $2:源柱子, $3:辅助柱子, $4:目标柱子
hanoi(){
    local n=$1
    local from=$2
    local buffer=$3
    local to=$4

    if [ $n -eq 1 ]; then
        echo "将第 1 个盘子从 $from 移到 $to"
    else
        # 步骤1: 将 n-1 个盘子从 源 -> 辅助 (借用 目标)
        hanoi $((n-1)) $from $to $buffer
        
        # 步骤2: 将第 n 个盘子从 源 -> 目标
        echo "将第 $n 个盘子从 $from 移到 $to"
        
        # 步骤3: 将 n-1 个盘子从 辅助 -> 目标 (借用 源)
        hanoi $((n-1)) $buffer $from $to
    fi
}

read -p "请输入汉诺塔的层数 (建议 3 或 4): " num
echo "--- 移动步骤如下 ---"
hanoi $num "A柱" "B柱" "C柱"
