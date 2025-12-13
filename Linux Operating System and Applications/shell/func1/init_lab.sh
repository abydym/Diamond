#!/bin/bash

echo "正在生成所有实验脚本..."

# --- (1) 参数调试脚本 ---
cat > exp_01_params.sh << 'EOF'
#!/bin/bash
# 题目要求：调试程序，理解变量含义
# $0: 当前脚本的文件名
# $#: 传递给脚本的参数总个数
# $@: 传递给脚本的所有参数列表
# $1-$9: 第1到第9个参数

echo "program name: $0"
echo "all parameters: $@"
echo "first three parameters: $1 $2 $3"

echo "--- 执行 shift (左移1位) ---"
shift
echo "program name: $0"
echo "all parameters: $@"
echo "first three parameters: $1 $2 $3"

echo "--- 执行 shift 3 (左移3位) ---"
shift 3
echo "program name: $0"
echo "all parameters: $@"
echo "first three parameters: $1 $2 $3"
exit 0
EOF

# --- (2) 文件判断脚本 ---
cat > exp_02_filecheck.sh << 'EOF'
#!/bin/bash
# 题目要求：输入文件名，判断是否存在，如果是目录则ls，如果是文件则显示内容

read -p "请输入文件或目录路径: " DORF

if [ -d "$DORF" ]; then
    echo "$DORF 是一个目录，内容如下："
    ls -l "$DORF"
elif [ -f "$DORF" ]; then
    echo "$DORF 是一个普通文件，内容如下："
    cat "$DORF"
else
    echo "文件不存在或不是普通文件/目录"
fi
EOF

# --- (3) Root目录操作1 (创建文件夹和文件) ---
cat > exp_03_root_op1.sh << 'EOF'
#!/bin/bash
# 题目要求：显示root文件信息，建立文件夹，新建文件aa并修改权限
# 注意：操作 /root 需要 sudo 权限

# 检查是否有权限访问 /root
if [ ! -r "/root" ]; then
    echo "权限不足，请使用 sudo ./exp_03_root_op1.sh 运行此脚本"
    exit 1
fi

echo "--- /root 目录内容 ---"
ls -l /root

read -p "请输入要在当前目录创建的文件夹名: " x
mkdir -p "$x"
cd "$x" || exit

echo "正在创建文件 aa ..."
# 原题提示 mkdir aa，但mkdir是创建目录，题目语境是“文件aa”，且后续要chmod +x
# 这里改为 touch aa 创建普通文件，更符合逻辑
touch aa
echo "echo 'Hello Linux'" > aa 

echo "修改权限为可执行..."
chmod +x aa

echo "操作完成，查看结果："
ls -l aa
EOF

# --- (4) Root目录操作2 (重定向信息到文件) ---
cat > exp_04_root_op2.sh << 'EOF'
#!/bin/bash
# 题目要求：将 /root 下的文件信息保存到 aa 中，并修改权限

target_file="aa"

# 检查权限
if [ ! -r "/root" ]; then
    echo "权限不足，请使用 sudo 运行"
    exit 1
fi

echo "正在将 /root 信息写入 $target_file ..."
ls -l /root > "$target_file"

echo "修改文件权限为可执行..."
chmod +x "$target_file"

echo "--- 文件内容如下 ---"
cat "$target_file"
EOF

# --- (5) 删除文件到回收站 ---
cat > exp_05_trash_del.sh << 'EOF'
#!/bin/bash
# 题目要求：删除指定文件到回收站 (压缩并移动)

# 1. 判断是否输入了参数
if [ $# -eq 0 ]; then
    echo "用法: $0 <要删除的文件名>"
    exit 1
fi

filename=$1
trash_dir="$HOME/.local/share/Trash/files"

# 2. 确保回收站目录存在
if [ ! -d "$trash_dir" ]; then
    mkdir -p "$trash_dir"
fi

# 3. 检查文件是否存在
if [ ! -f "$filename" ]; then
    echo "错误：文件 $filename 不存在"
    exit 1
fi

# 4. 压缩并移动
echo "正在将 $filename 移入回收站..."
gzip "$filename"
mv "${filename}.gz" "$trash_dir"

echo "删除成功。"
EOF

# --- (6) 恢复回收站文件 ---
cat > exp_06_trash_restore.sh << 'EOF'
#!/bin/bash
# 题目要求：查看回收站，输入文件名，恢复到 $HOME

trash_dir="$HOME/.local/share/Trash/files"

echo "--- 回收站 ($trash_dir) 内容 ---"
ls "$trash_dir"

read -p "请输入要恢复的文件名 (不带 .gz 后缀): " restore_file

if [ -f "$trash_dir/${restore_file}.gz" ]; then
    echo "正在恢复..."
    # 移动回 HOME
    mv "$trash_dir/${restore_file}.gz" "$HOME/"
    # 解压
    gzip -d "$HOME/${restore_file}.gz"
    echo "恢复成功：$HOME/$restore_file"
else
    echo "错误：回收站中找不到 ${restore_file}.gz"
fi
EOF

# --- (7) 清空回收站 ---
cat > exp_07_trash_empty.sh << 'EOF'
#!/bin/bash
# 题目要求：删除垃圾箱中的所有文件

trash_dir="$HOME/.local/share/Trash/files"

read -p "警告：确定要清空回收站吗？(y/n): " choice
if [ "$choice" == "y" ]; then
    rm -rf "${trash_dir:?}"/*
    echo "回收站已清空。"
else
    echo "取消操作。"
fi
EOF

# --- (8) While循环求和 (1-100) ---
cat > exp_08_sum_while.sh << 'EOF'
#!/bin/bash
# 题目要求：while循环求1到100的和

total=0
num=0

while ((num <= 100))
do
   # expr 是比较老的写法，但在实验中很常见
   total=`expr $total + $num`
   ((num+=1))
done

echo "The result (While) is $total"
EOF

# --- (9) For循环求和 (1-100) ---
cat > exp_09_sum_for.sh << 'EOF'
#!/bin/bash
# 题目要求：用 for 语句完成求和

total=0
# 使用 {1..100} 生成序列
for i in {1..100}
do
    total=$((total + i))
done

echo "The result (For) is $total"
EOF

# --- (10) 调和级数求和 (1+1/2+...+1/n) ---
cat > exp_10_harmonic.sh << 'EOF'
#!/bin/bash
# 题目要求：计算 1+1/2+1/3+...+1/n
# 注意：Shell 默认不支持浮点运算，这里使用 awk 实现

read -p "请输入 n 的值: " n

# 使用 awk 进行浮点数累加
result=$(awk -v num="$n" 'BEGIN {
    sum = 0;
    for (i = 1; i <= num; i++) {
        sum += 1/i;
    }
    print sum;
}')

echo "1+1/2+...+1/$n 的结果是: $result"
EOF

# --- (11) 文件管理菜单系统 ---
cat > exp_11_menu_files.sh << 'EOF'
#!/bin/bash
# 题目要求：菜单实现 ls, cd, touch, vi, rm

until [ "$choice" == "6" ]
do
    echo "======================"
    echo "   文件管理系统菜单"
    echo "======================"
    echo "1. 目录内容 (ls)"
    echo "2. 切换目录 (cd)"
    echo "3. 创建文件 (touch)"
    echo "4. 编辑文件 (vim)" # 实验环境一般用 vim 或 nano
    echo "5. 删除文件 (rm)"
    echo "6. 退出"
    echo "----------------------"
    read -p "请输入选项 (1-6): " choice

    case "$choice" in
        1) 
            ls -l 
            ;;
        2) 
            read -p "请输入目录路径: " dir_path
            if [ -d "$dir_path" ]; then
                cd "$dir_path"
                echo "已切换到: $(pwd)"
                # 注意：子shell中切换目录不会影响父shell，但在当前脚本循环中有效
            else
                echo "目录不存在"
            fi
            ;;
        3) 
            read -p "请输入文件名: " fname
            touch "$fname"
            echo "文件创建成功"
            ;;
        4) 
            read -p "请输入文件名: " fname
            vim "$fname"
            ;;
        5) 
            read -p "请输入要删除的文件名: " fname
            rm -i "$fname" 
            ;;
        6) 
            echo "退出系统" 
            ;;
        *) 
            echo "无效输入，请重试" 
            ;;
    esac
    echo "" 
done
EOF

# --- (12) 四则运算菜单系统 ---
cat > exp_12_menu_calc.sh << 'EOF'
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
EOF

# --- (13) 递归遍历 (Tree模拟) ---
cat > exp_13_tree_sim.sh << 'EOF'
#!/bin/bash
# 题目要求：分析程序运行结果 (模拟 Windows 的 tree 命令)

xx=0

func(){
    # 获取当前路径的父目录部分，这里主要用于显示逻辑
    dire=${PWD%/*} 
    
    # 遍历当前目录下的所有文件
    for file in $(ls); do
        if [ -f "$file" ]; then
            # 如果是文件，打印缩进和文件名
            i=$xx
            while [ $i -gt 0 ]; do
                echo -e "  |\c" # 模拟树状缩进
                i=`expr $i - 1`
            done
            echo -e "-- $file"
            
        elif [ -d "$file" ]; then
            # 如果是目录，进入目录并递归
            echo -e "-- [Directory: $file]"
            cd "$file"
            xx=$(( $xx + 1 )) # 缩进层级 +1
            func              # 递归调用
            cd ..             # 返回上一级
            xx=$(( $xx - 1 )) # 缩进层级 -1
        fi
    done
}

echo "正在生成目录树..."
func

echo ""
echo "==========================================="
echo "分析：此程序的功能类似于 Windows/Linux 的 'tree' 命令"
echo "它递归地列出目录下的所有子目录和文件结构。"
echo "==========================================="
EOF

# --- 权限设置 ---
chmod +x exp_*.sh
echo "所有文件已生成，且已赋予执行权限！"
echo "你可以通过输入 ./exp_ 并在按 Tab 键来查看和运行它们。"
ls -l exp_*.sh
