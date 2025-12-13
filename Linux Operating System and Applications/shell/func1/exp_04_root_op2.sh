#!/bin/bash
# 题目要求：将 /root 下的文件信息保存到 aa 中，并修改权限

target_file="aa"

# 检查权限
if [ ! -r "/root" ]; then
    echo "权限不足，请使用 sudo 运行"
    exit 1
fi

echo "正在将 /root 信息写入 $target_file ..."
ls -l /root > "$target_file"

echo "修改文件权限为可执行..."
chmod +x "$target_file"

echo "--- 文件内容如下 ---"
cat "$target_file"
