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
