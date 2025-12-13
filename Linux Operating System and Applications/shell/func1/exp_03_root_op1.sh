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
