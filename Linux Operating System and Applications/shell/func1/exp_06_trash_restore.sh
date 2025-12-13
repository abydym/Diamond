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
