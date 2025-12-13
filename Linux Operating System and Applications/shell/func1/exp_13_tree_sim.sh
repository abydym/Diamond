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
