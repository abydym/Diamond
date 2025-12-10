#!/bin/bash

a="abc"
b="efg"

# 1. 检测两个字符串是否相等 (=)
if [ "$a" = "$b" ]
then
   echo "$a = $b : a 等于 b"
else
   echo "$a = $b : a 不等于 b"
fi

# 2. 检测两个字符串是否不相等 (!=)
if [ "$a" != "$b" ]
then
   echo "$a != $b : a 不等于 b"
else
   echo "$a != $b : a 等于 b"
fi

# 3. 检测字符串长度是否为 0 (-z)
# -z 意为 Zero (空)
if [ -z "$a" ]
then
   echo "-z $a : 字符串长度为 0 (是空字符串)"
else
   echo "-z $a : 字符串长度不为 0"
fi

# 4. 检测字符串长度是否不为 0 (-n)
# -n 意为 Non-zero (非空)
if [ -n "$a" ]
then
   echo "-n $a : 字符串长度不为 0"
else
   echo "-n $a : 字符串长度为 0"
fi

# 5. 直接检测字符串是否为空 (str)
# 如果字符串不为空，返回 true
if [ "$a" ]
then
   echo "$a : 字符串不为空"
else
   echo "$a : 字符串为空"
fi
