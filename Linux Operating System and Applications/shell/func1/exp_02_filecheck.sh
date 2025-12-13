#!/bin/bash
# 题目要求：输入文件名，判断是否存在，如果是目录则ls，如果是文件则显示内容

read -p "请输入文件或目录路径: " DORF

if [ -d "$DORF" ]; then
    echo "$DORF 是一个目录，内容如下："
    ls -l "$DORF"
elif [ -f "$DORF" ]; then
    echo "$DORF 是一个普通文件，内容如下："
    cat "$DORF"
else
    echo "文件不存在或不是普通文件/目录"
fi
