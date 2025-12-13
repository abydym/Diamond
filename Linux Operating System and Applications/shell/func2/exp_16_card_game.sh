#!/bin/bash
# 题目要求：扑克牌抽牌比大小游戏
# 修复了原文中的语法错误

# 1. 初始化牌堆 (ok数组标记牌是否被抽过，1代表在牌堆中)
for i in $(seq 1 54)
do
    ok[$i]=1
done

max=0 # 记录当前最大的点数
num=0 # 记录赢家是谁

# 2. 游戏开始，4个玩家
for i in $(seq 1 4)
do
    echo "----------------"
    echo "Player $i 抽牌中..."
    
    # 随机抽一张牌 (1-53)
    # 原题逻辑是 RANDOM%53+1，这意味着很难抽到 54(大王)，我们尊重原题逻辑
    a=$((RANDOM%53+1))
    
    # 如果这张牌已经被抽过了(ok[a]==0)，就重抽
    while [[ ${ok[$a]} -eq 0 ]]; do
        a=$((RANDOM%53+1))
    done
    
    # 标记这张牌已被抽走
    ok[$a]=0
    
    # 比较大小，记录最大值
    if [ $a -gt $max ]; then
        max=$a
        num=$i
    fi

    # 计算花色 (0-3)
    HuaSe=$((a%4))
    case $HuaSe in
        0) HS='梅花(Club)';;
        1) HS='方块(Diamond)';;
        2) HS='红心(Heart)';;
        3) HS='黑桃(Spade)';;
    esac

    # 计算牌面大小
    DaXiao=$((a/4+1))
    
    # 显示牌面
    case $DaXiao in
        2|3|4|5|6|7|8|9|10) echo "抽到了: $HS $DaXiao";;
        11) echo "抽到了: $HS J";;
        12) echo "抽到了: $HS Q";;
        13) echo "抽到了: $HS K";;
        1)  echo "抽到了: $HS A";;
        14) echo "抽到了: 小王 (Small Joker)";;
        15) echo "抽到了: 大王 (Big Joker)";;
        *)  echo "未知牌型";;
    esac
    
    # 原题这里有个 read ll 暂停，为了流畅我注释掉了，或者保留
    # read -p "按回车继续..." ll
done

echo "======================"
echo "最终赢家是: Player $num !"
echo "======================"
