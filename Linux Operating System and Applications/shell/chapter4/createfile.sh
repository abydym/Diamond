#!/bin/bash
# 批量在指定目录创建 100 个文件

# 定义目标目录
target_dir="./headless/shell/chapter4/file"

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
