#!/bin/bash
# judge.sh - 判断闰年
read -p "请输入一个年份: " year

# 闰年规则：能被4整除且不能被100整除，或者能被400整除
if [ $((year % 4)) -eq 0 ] && [ $((year % 100)) -ne 0 ] || [ $((year % 400)) -eq 0 ]; then
    echo "$year 是闰年"
else
    echo "$year 不是闰年"
fi
