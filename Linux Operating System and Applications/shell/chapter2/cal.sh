#!/bin/bash
# cal.sh - 简易计算器

# 1. 输入两个数字
read -p "请输入两个数字 (用空格隔开): " num1 num2

# 2. 输入运算符
read -p "请输入运算符 (+ - * /): " op

# 3. 根据运算符进行计算
case "$op" in
    +)
        result=$((num1 + num2))
        ;;
    -)
        result=$((num1 - num2))
        ;;
    \*) 
        # 注意：这里写 \* 是为了防止 * 被当做通配符（代表“所有其他情况”）
        result=$((num1 * num2))
        ;;
    /)
        # 这里简单处理，不考虑除数为0的情况
        result=$((num1 / num2))
        ;;
    *)
        echo "输入错误：无效的运算符"
        exit 1
        ;;
esac

echo "计算结果: $result"
