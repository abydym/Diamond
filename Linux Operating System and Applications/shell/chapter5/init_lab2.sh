#!/bin/bash

# 1. 准备目录 chapter5 (确保它存在，因为第4题要用到)
mkdir -p chapter5

# --- 2. sum.sh: 函数加法运算 ---
cat > chapter5/sum.sh << 'EOF'
#!/bin/bash
# sum.sh - 函数实现两个整数加法

# 定义 sum 函数
sum_func(){
    # $1 和 $2 是函数接收到的第一个和第二个参数
    res=$(($1 + $2))
    echo "两数之和为: $res"
}

read -p "请输入第一个整数: " n1
read -p "请输入第二个整数: " n2

# 调用函数，并将用户输入的变量作为参数传递进去
sum_func $n1 $n2
EOF

# --- 3. fib.sh: 递归版斐波那契数列 ---
cat > chapter5/fib.sh << 'EOF'
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
EOF

# --- 4. judge.sh: 目录判断与文件移动 ---
# (你原题写的是 judeg.sh，我帮你修正为 judge.sh)
cat > chapter5/judge.sh << 'EOF'
#!/bin/bash
# judge.sh - 目录判断逻辑

target_dir="/headless/test"
source_dir="/headless/shell/chapter5"

# 判断目标目录是否存在 (-d)
if [ -d "$target_dir" ]; then
    echo "目录 $target_dir 存在。"
    echo "正在将 $source_dir 下的所有文件移动到 $target_dir ..."
    
    # 检查源目录是否有文件，避免报错
    if [ "$(ls -A $source_dir)" ]; then
       # 移动文件 (使用 sudo 确保权限，如果是在 root 下则不需要)
       mv "$source_dir"/* "$target_dir"/
       echo "移动完成。"
    else
       echo "源目录为空，无需移动。"
    fi
else
    echo "目录 $target_dir 不存在。"
    echo "正在创建该目录..."
    mkdir -p "$target_dir"
    echo "目录创建成功，脚本退出。"
    exit 0
fi
EOF

# --- 5. Hanoi.sh: 汉诺塔递归 ---
cat > chapter5/Hanoi.sh << 'EOF'
#!/bin/bash
# Hanoi.sh - 汉诺塔移动步骤

# 定义移动函数
# 参数含义: $1:盘子数, $2:源柱子, $3:辅助柱子, $4:目标柱子
hanoi(){
    local n=$1
    local from=$2
    local buffer=$3
    local to=$4

    if [ $n -eq 1 ]; then
        echo "将第 1 个盘子从 $from 移到 $to"
    else
        # 步骤1: 将 n-1 个盘子从 源 -> 辅助 (借用 目标)
        hanoi $((n-1)) $from $to $buffer
        
        # 步骤2: 将第 n 个盘子从 源 -> 目标
        echo "将第 $n 个盘子从 $from 移到 $to"
        
        # 步骤3: 将 n-1 个盘子从 辅助 -> 目标 (借用 源)
        hanoi $((n-1)) $buffer $from $to
    fi
}

read -p "请输入汉诺塔的层数 (建议 3 或 4): " num
echo "--- 移动步骤如下 ---"
hanoi $num "A柱" "B柱" "C柱"
EOF

# --- 统一设置权限 ---
echo "正在生成文件并设置权限..."
chmod +x chapter5/sum.sh chapter5/fib.sh chapter5/judge.sh chapter5/Hanoi.sh

echo "================================================="
echo "任务完成！所有脚本已生成在 chapter5 目录下。"
echo "注意：fib.sh 和 Hanoi.sh 使用递归，数字不要输太大。"
echo "================================================="
ls -l chapter5/
