#!/bin/bash

# 定义要检测的文件路径
file="/headless/shell/chapter1/hello.sh"

# 1. 检测文件是否可读 (-r: read)
if [ -r "$file" ]
then
   echo "文件可读"
else
   echo "文件不可读"
fi

# 2. 检测文件是否可写 (-w: write)
if [ -w "$file" ]
then
   echo "文件可写"
else
   echo "文件不可写"
fi

# 3. 检测文件是否可执行 (-x: execute)
if [ -x "$file" ]
then
   echo "文件可执行"
else
   echo "文件不可执行"
fi

# 4. 检测文件是否为普通文件 (-f: file)
# 也就是判断它不是目录、不是设备文件
if [ -f "$file" ]
then
   echo "文件为普通文件"
else
   echo "文件为特殊文件 (或不存在)"
fi

# 5. 检测文件是否为目录 (-d: directory)
if [ -d "$file" ]
then
   echo "文件是个目录"
else
   echo "文件不是个目录"
fi

# 6. 检测文件是否不为空 (-s: size)
# 如果文件大小大于0，返回 true
if [ -s "$file" ]
then
   echo "文件不为空"
else
   echo "文件为空"
fi

# 7. 检测文件是否存在 (-e: exists)
if [ -e "$file" ]
then
   echo "文件存在"
else
   echo "文件不存在"
fi
