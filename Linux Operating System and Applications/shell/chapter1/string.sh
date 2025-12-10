#!/bin/bash
# string.sh - 字符串反转与拼接

# 1. 输入两个字符串
read -p "请输入第一个字符串 (str1): " str1
read -p "请输入第二个字符串 (str2): " str2

# 2. 将字符串 str2 反转输出
# 使用 rev 命令
str2_reversed=$(echo "$str2" | rev)
echo "str2 反转后的结果: $str2_reversed"

# 3. 拼接 str1 和 str2
combined_str="${str1}${str2}"
echo "拼接后的字符串: $combined_str"

# 4. 输出拼接后的长度
length=${#combined_str}
echo "拼接后的字符串长度: $length"
