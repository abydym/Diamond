#!/bin/bash
# 题目要求：输入路径，提供菜单：删除特定类型、删除除某文件外的文件、删除所有、退出

echo "--- 文件清理助手 ---"
read -p "请输入目标目录路径: " target_dir

if [ ! -d "$target_dir" ]; then
    echo "错误：目录不存在！"
    exit 1
fi

cd "$target_dir" || exit

while true; do
    echo "---------------------------"
    echo "当前目录: $(pwd)"
    echo "1. 删除指定后缀的文件 (例如删除所有 .txt)"
    echo "2. 删除目录或文件 (指定名称)"
    echo "3. 删除某文件外的其他所有文件 (保留一个)"
    echo "4. 删除当前目录下所有文件 (清空)"
    echo "5. 退出"
    echo "---------------------------"
    read -p "请选择操作 (1-5): " choice

    case "$choice" in
        1)
            read -p "请输入要删除的文件后缀 (如 txt): " ext
            # 确认一下，防止误删
            read -p "确定删除所有 .$ext 文件吗? (y/n): " confirm
            if [ "$confirm" == "y" ]; then
                rm *."$ext" 2>/dev/null
                echo "删除完成。"
            fi
            ;;
        2)
            read -p "请输入要删除的文件或文件夹名: " name
            rm -rf "$name"
            echo "已删除 $name"
            ;;
        3)
            read -p "请输入要【保留】的文件名: " keep_file
            if [ -e "$keep_file" ]; then
                # 使用 find 命令查找不是该文件的项目并删除
                # -maxdepth 1 保证只操作当前层级
                find . -maxdepth 1 ! -name "$keep_file" ! -name "." -exec rm -rf {} +
                echo "已删除除 $keep_file 外的所有文件。"
            else
                echo "错误：当前目录下找不到 $keep_file"
            fi
            ;;
        4)
            read -p "警告：确定清空当前目录所有内容吗？(y/n): " confirm
            if [ "$confirm" == "y" ]; then
                rm -rf ./*
                echo "目录已清空。"
            fi
            ;;
        5)
            echo "退出程序。"
            break
            ;;
        *)
            echo "无效输入。"
            ;;
    esac
done
