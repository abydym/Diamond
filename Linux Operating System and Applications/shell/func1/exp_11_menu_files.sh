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
