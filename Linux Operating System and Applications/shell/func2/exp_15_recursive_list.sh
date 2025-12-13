#!/bin/bash
# 题目要求：补全程序，实现 ls -R 功能 (递归遍历子目录)

# 定义 list 函数
list(){
    local current_dir=$1
    
    # 切换到目标目录，如果失败则返回
    cd "$current_dir" || return
    
    echo ""
    echo "Directory: $current_dir"
    echo "-----------------------"
    ls -l | grep "^-"  # 先显示当前目录下的文件

    # 遍历当前目录下的所有项
    for i in *
    do 
        # 如果是目录，且不是 . 或 ..
        if [ -d "$i" ]; then
             full_path="$current_dir/$i"
             echo "-> Found subdirectory: $full_path"
             
             # 【递归调用】核心点
             list "$full_path"
             
             # 递归返回后，必须切回当前目录，否则后续循环会出错
             cd "$current_dir"
        fi 
    done 
}

# 主程序开始
read -p "请输入要遍历的目录 (绝对路径): " start_dir

if [ -d "$start_dir" ]; then
    echo "开始遍历..."
    list "$start_dir"
else
    echo "目录不存在"
fi
