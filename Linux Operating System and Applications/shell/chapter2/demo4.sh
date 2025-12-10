#!/bin/bash

a=10
b=20

# 1. 逻辑与 (AND) 测试
# 语法：[[ 条件1 && 条件2 ]]
# 逻辑：a(10)小于100 (真) 且 b(20)大于100 (假) -> 结果为 假
if [[ $a -lt 100 && $b -gt 100 ]]
then
   echo "返回 true"
else
   echo "返回 false"
fi

# 2. 逻辑或 (OR) 测试
# 语法：[[ 条件1 || 条件2 ]]
# 逻辑：a(10)小于100 (真) 或 b(20)大于100 (假) -> 只要有一个真，结果即为 真
if [[ $a -lt 100 || $b -gt 100 ]]
then
   echo "返回 true"
else
   echo "返回 false"
fi
