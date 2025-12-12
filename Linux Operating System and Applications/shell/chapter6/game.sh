#!/bin/bash
# game.sh - 猜数字游戏 (1-100)

# 生成 1-100 的随机数
# $RANDOM 是 shell 内置随机变量，% 100 取余数得到 0-99，再 +1 得到 1-100
target=$((RANDOM % 100 + 1))

echo "我已经想好了一个 1 到 100 之间的数字，请猜猜看！"

while true
do
    read -p "请输入你的猜测: " guess

    # 判断是否猜对 (-eq)
    if [ "$guess" -eq "$target" ]; then
        echo "恭喜你！猜对了！答案就是 $target"
        break  # 跳出循环，脚本结束
    elif [ "$guess" -gt "$target" ]; then
        echo "猜大了，再试一次。"
    else
        echo "猜小了，再试一次。"
    fi
done
