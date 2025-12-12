#!/bin/bash
# fib.sh - 递归计算斐波那契 (1, 1, 2, 3, 5...)
# 警告：Shell 递归效率极低，测试时请输入较小的数字（如 10 以内），否则会卡死！

fib(){
    local n=$1
    if [ $n -le 2 ]; then
        echo 1
    else
        # 递归调用：F(n) = F(n-1) + F(n-2)
        # 这里使用了命令替换 $() 来获取递归调用的结果
        echo $(( $(fib $((n-1))) + $(fib $((n-2))) ))
    fi
}

read -p "请输入要计算第几项斐波那契数 (建议<15): " num
start_time=$(date +%s)
result=$(fib $num)
end_time=$(date +%s)

echo "斐波那契数列第 $num 项是: $result"
echo "耗时: $((end_time - start_time)) 秒"
