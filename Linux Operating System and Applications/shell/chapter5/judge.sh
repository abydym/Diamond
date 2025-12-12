#!/bin/bash
# judge.sh - 目录判断逻辑

target_dir="./headless/test"
source_dir="./headless/shell/chapter5"

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
