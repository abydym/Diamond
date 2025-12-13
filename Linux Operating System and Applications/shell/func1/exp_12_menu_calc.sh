#!/bin/bash
# 题目要求：菜单形式完成两个数的四则运算

while true
do
    echo "=== 简易计算器 ==="
    echo "1. 加法 (+)"
    echo "2. 减法 (-)"
    echo "3. 乘法 (*)"
    echo "4. 除法 (/)"
    echo "5. 退出"
    read -p "请选择运算模式: " mode

    if [ "$mode" == "5" ]; then
        echo "再见！"
        break
    fi

    read -p "请输入第一个数: " n1
    read -p "请输入第二个数: " n2

    case "$mode" in
        1) echo "$n1 + $n2 = $((n1 + n2))" ;;
        2) echo "$n1 - $n2 = $((n1 - n2))" ;;
        3) echo "$n1 * $n2 = $((n1 * n2))" ;;
        4) 
            # 简单的除法处理
            if [ "$n2" -eq 0 ]; then
                echo "错误：除数不能为0"
            else
                #以此例保留两位小数，需用 awk
                res=$(awk "BEGIN {printf \"%.2f\", $n1/$n2}")
                echo "$n1 / $n2 = $res" 
            fi
            ;;
        *) echo "无效选项" ;;
    esac
    echo ""
done
