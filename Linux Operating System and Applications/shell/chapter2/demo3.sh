#!/bin/bash

# 定义变量
a=10
b=20

echo "--- 测试 1: 非运算 (!) ---"
# 原图逻辑：如果 a 不等于 b
if [ $a != $b ]
then
   echo "$a != $b : a 不等于 b"
else
   echo "$a == $b : a 等于 b"
fi

echo ""
echo "--- 测试 2: 与运算 (-a) ---"
# 原图逻辑：a小于100 且 b大于15
# -a (and) 表示“并且”，两边条件都成立才返回 true
if [ $a -lt 100 -a $b -gt 15 ]
then
   echo "$a 小于 100 且 $b 大于 15 : 返回 true"
else
   echo "$a 小于 100 且 $b 大于 15 : 返回 false"
fi

echo ""
echo "--- 测试 3: 或运算 (-o) ---"
# 原图逻辑：a小于100 或 b大于100
# -o (or) 表示“或者”，只要有一边成立就返回 true
if [ $a -lt 100 -o $b -gt 100 ]
then
   echo "$a 小于 100 或 $b 大于 100 : 返回 true"
else
   echo "$a 小于 100 或 $b 大于 100 : 返回 false"
fi

echo ""
echo "--- 测试 4: 或运算 (-o) ---"
# 原图逻辑：a小于5 或 b大于100
if [ $a -lt 5 -o $b -gt 100 ]
then
   echo "$a 小于 5 或 $b 大于 100 : 返回 true"
else
   echo "$a 小于 5 或 $b 大于 100 : 返回 false"
fi
