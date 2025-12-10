#!/bin/bash

# --- 2. 闰年判断脚本 (judge.sh) ---
cat > judge.sh << 'EOF'
#!/bin/bash
# judge.sh - 判断闰年
read -p "请输入一个年份: " year

# 闰年规则：能被4整除且不能被100整除，或者能被400整除
if [ $((year % 4)) -eq 0 ] && [ $((year % 100)) -ne 0 ] || [ $((year % 400)) -eq 0 ]; then
    echo "$year 是闰年"
else
    echo "$year 不是闰年"
fi
EOF

# --- 3. 剪刀石头布游戏 (game.sh) ---
cat > game.sh << 'EOF'
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
EOF

# --- 4. 账户名数组统计 (user.sh) ---
cat > user.sh << 'EOF'
#!/bin/bash
# user.sh - 账户名数组处理

# -a 选项允许将输入直接读入数组
read -p "请输入账户名称 (多个名称用空格隔开): " -a names

echo "------------------------"
# ${#names[@]} 获取数组长度
echo "账户名的数量: ${#names[@]}"

# ${names[@]} 获取数组所有元素
echo "保存的账户名: ${names[@]}"
echo "------------------------"
EOF

# --- 统一设置权限 ---
echo "正在生成文件并设置权限..."
chmod +x judge.sh game.sh user.sh

echo "======================================"
echo "任务完成！以下脚本已生成并可执行："
ls -l judge.sh game.sh user.sh
echo "======================================"
