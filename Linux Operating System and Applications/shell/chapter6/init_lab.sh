#!/bin/bash

# --- 2. 猜数字游戏 (game.sh) ---
cat > game.sh << 'EOF'
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
EOF

# --- 3. 三个数排序 (sort.sh) ---
cat > sort.sh << 'EOF'
#!/bin/bash
# sort.sh - 输入三个数升序输出

echo "请输入三个数 (用空格隔开):"
read a b c

echo "升序排序结果:"
# echo -e 将三个数分行输出，然后通过管道 | 传给 sort 命令
# sort -n 表示按“数值”大小排序 (numeric)，而不是按字符排序
echo -e "$a\n$b\n$c" | sort -n
EOF

# --- 4. 大小写转换 (change.sh) ---
cat > change.sh << 'EOF'
#!/bin/bash
# change.sh - 小写转大写

read -p "请输入一个字符串: " str

# 使用 tr 命令进行转换
# 'a-z' 代表所有小写，'A-Z' 代表所有大写
result=$(echo "$str" | tr 'a-z' 'A-Z')

echo "转换后的结果: $result"

# 补充知识：Bash 4.0+ 也可以用 echo "${str^^}" 这种写法
EOF

# --- 统一设置权限 ---
echo "正在当前目录下生成脚本并设置权限..."
chmod +x game.sh sort.sh change.sh

echo "======================================"
echo "任务完成！以下脚本已生成在当前目录："
ls -l game.sh sort.sh change.sh
echo "======================================"``
