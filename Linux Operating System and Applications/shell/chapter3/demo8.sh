#!/bin/bash
echo hello; echo there         # 输出 hello 和 there
filename='demo2.sh'            # 变量
if [ -x "$filename" ]; then    # 注意："if" and "then"需要分隔符
    echo "File $filename exists."
    cp $filename $filename.bak
else
    echo "File $filename not found."
    touch $filename
fi
echo "File test complete."
