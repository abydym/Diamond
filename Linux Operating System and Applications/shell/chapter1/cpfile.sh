#!/bin/bash
# cpfile.sh - 文件创建与复制操作

# 定义基础路径
BASE_DIR="/headless"

# 1. 创建目录 /headless/test (-p 确保父目录不存在时自动创建，且目录已存在时不报错)
mkdir -p "$BASE_DIR/test"
echo "目录 $BASE_DIR/test 已创建。"

# 2. 创建 test1.txt 内容为 hello
echo "hello" > "$BASE_DIR/test/test1.txt"

# 3. 创建 test2.txt 内容为 wrold (严格按照题目要求拼写)
echo "wrold" > "$BASE_DIR/test/test2.txt"
echo "文件 test1.txt 和 test2.txt 已创建。"

# 4. 创建目标目录 /headless/test1
mkdir -p "$BASE_DIR/test1"

# 5. 复制 test 目录下的所有内容到 test1 目录下
# cp -r 递归复制
cp -r "$BASE_DIR/test/"* "$BASE_DIR/test1/"

echo "已将 $BASE_DIR/test 的内容复制到 $BASE_DIR/test1"
echo "操作完成。"


# 验证一下结果 (可选)
echo "--- 验证结果 ---"
ls -R "$BASE_DIR/test1"
