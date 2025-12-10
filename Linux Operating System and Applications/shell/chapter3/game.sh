#!/bin/bash
# game.sh - 人机猜拳
echo "--- 猜拳游戏 ---"
echo "1. 剪刀"
echo "2. 石头"
echo "3. 布"
read -p "请出拳 (输入 1-3): " person

# 电脑随机生成 1-3
# RANDOM 生成随机整数，% 3 取余得到 0-2，再 +1 得到 1-3
num=$((RANDOM % 3 + 1))

# 显示电脑出的拳
case $num in
    1) echo "电脑出了: 剪刀";;
    2) echo "电脑出了: 石头";;
    3) echo "电脑出了: 布";;
esac

# 判断胜负
if [ "$person" -eq "$num" ]; then
    echo "结果: 平局！"
elif [ "$person" -eq 1 ] && [ "$num" -eq 3 ] || \
     [ "$person" -eq 2 ] && [ "$num" -eq 1 ] || \
     [ "$person" -eq 3 ] && [ "$num" -eq 2 ]; then
    echo "结果: 你赢了！"
else
    echo "结果: 你输了！(电脑赢)"
fi
