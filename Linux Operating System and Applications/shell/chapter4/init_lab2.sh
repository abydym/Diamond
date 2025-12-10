#!/bin/bash

# 1. 先准备好存放脚本的目录 chapter4
mkdir -p chapter4

# --- 2.1 mul-1.sh: 99乘法表 (只用 for) ---
cat > chapter4/mul-1.sh << 'EOF'
#!/bin/bash
# 只使用 for 循环实现 99 乘法表
echo "--- For 循环乘法表 ---"
for ((i=1; i<=9; i++))
do
    for ((j=1; j<=i; j++))
    do
        # -n 不换行, \t 制表符对齐
        echo -n -e "$j*$i=$((i*j))\t"
    done
    echo "" # 换行
done
EOF

# --- 2.2 mul-2.sh: 99乘法表 (只用 while) ---
cat > chapter4/mul-2.sh << 'EOF'
#!/bin/bash
# 只使用 while 循环实现 99 乘法表
echo "--- While 循环乘法表 ---"
i=1
while [ $i -le 9 ]
do
    j=1
    while [ $j -le $i ]
    do
        echo -n -e "$j*$i=$((i*j))\t"
        let j++
    done
    echo "" # 换行
    let i++
done
EOF

# --- 2.3 mul-3.sh: 99乘法表 (for 与 while 结合) ---
cat > chapter4/mul-3.sh << 'EOF'
#!/bin/bash
# 外层用 for，内层用 while
echo "--- For + While 混合乘法表 ---"
for ((i=1; i<=9; i++))
do
    j=1
    while [ $j -le $i ]
    do
        echo -n -e "$j*$i=$((i*j))\t"
        let j++
    done
    echo ""
done
EOF

# --- 3. single.sh: 数字等边三角形 ---
cat > chapter4/single.sh << 'EOF'
#!/bin/bash
# 输出数字等边三角形
# 规律：第 i 行，打印数字 i，打印次数为 2*i - 1，前方空格数为 总行数-i

# 默认边长为3，也可以让用户输入
read -p "请输入三角形边长 (默认3): " n
if [ -z "$n" ]; then n=3; fi

for ((i=1; i<=n; i++))
do
    # 1. 打印前导空格 (为了让三角形居中)
    for ((s=n-i; s>0; s--)); do
        echo -n " "
    done

    # 2. 打印数字
    # 计算该行需要打印多少个数字 (2*i - 1)
    count=$((2*i - 1))
    for ((k=1; k<=count; k++)); do
        echo -n "$i"
    done

    # 3. 换行
    echo ""
done
EOF

# --- 4. createfile.sh: 批量创建文件 ---
cat > chapter4/createfile.sh << 'EOF'
#!/bin/bash
# 批量在指定目录创建 100 个文件

# 定义目标目录
target_dir="/headless/shell/chapter4/file"

# 1. 判断目录是否存在，不存在则创建 (-p 递归创建)
if [ ! -d "$target_dir" ]; then
    echo "目录不存在，正在创建: $target_dir"
    mkdir -p "$target_dir"
fi

# 2. 循环创建文件
echo "开始在 $target_dir 下创建文件..."
for ((i=1; i<=100; i++))
do
    touch "$target_dir/file$i"
done

echo "完成！已创建 file1 到 file100。"
echo "当前目录文件数: $(ls -l $target_dir | grep "^-" | wc -l)"
EOF

# --- 统一设置权限 ---
echo "正在生成文件并设置权限..."
chmod +x chapter4/mul-1.sh chapter4/mul-2.sh chapter4/mul-3.sh chapter4/single.sh chapter4/createfile.sh

echo "================================================="
echo "任务完成！所有脚本已生成在 chapter4 目录下："
ls -l chapter4/
echo "================================================="
