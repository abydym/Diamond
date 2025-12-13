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
