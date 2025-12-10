#!/bin/bash

# --- Demo 1 ---
cat > demo1.sh << 'EOF'
#!/bin/bash
echo "Shell 传递参数实例！"
echo "执行的文件名：$0"
echo "第一个参数为：$1"
echo "第二个参数为：$2"
echo "第三个参数为：$3"
EOF

# --- Demo 2 ---
cat > demo2.sh << 'EOF'
#!/bin/bash
echo "Shell 传递参数实例！"
echo "第一个参数为：$1"
echo "参数个数为：$#"
echo "传递的参数作为一个字符串显示：$*"
EOF

# --- Demo 3 ---
cat > demo3.sh << 'EOF'
#!/bin/bash
echo "-- \$* 演示 ---"
for i in "$*"; do
    echo $i
done

echo "-- \$@ 演示 ---"
for i in "$@"; do
    echo $i
done
EOF

# --- Demo 4 ---
cat > demo4.sh << 'EOF'
#!/bin/bash
my_array=(A B "C" D)
echo "第一个元素为: ${my_array[0]}"
echo "第二个元素为: ${my_array[1]}"
echo "第三个元素为: ${my_array[2]}"
echo "第四个元素为: ${my_array[3]}"
EOF

# --- Demo 5 ---
cat > demo5.sh << 'EOF'
#!/bin/bash
my_array[0]=A
my_array[1]=B
my_array[2]=C
my_array[3]=D
echo "数组的元素为: ${my_array[*]}"
echo "数组的元素为: ${my_array[@]}"
EOF

# --- Demo 6 ---
cat > demo6.sh << 'EOF'
#!/bin/bash
my_array[0]=A
my_array[1]=B
my_array[2]=C
my_array[3]=D
echo "数组元素个数为: ${#my_array[*]}"
echo "数组元素个数为: ${#my_array[@]}"
EOF

# --- Demo 7 ---
cat > demo7.sh << 'EOF'
#!/bin/bash
echo "这里的 # 不会被注释"
echo '这里的 # 不会被注释'
echo 这里的 \# 不会被注释
echo 这里的 # 会被注释
echo ${PATH#*:}       # 前面的#是参数代换，不是注释.
echo $(( 2#101011 ))  # 基本转换，不是注释.
EOF

# --- Demo 8 ---
cat > demo8.sh << 'EOF'
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
EOF

# --- Demo 9 ---
cat > demo9.sh << 'EOF'
#!/bin/bash
read Keypress  #在终端输入一个字符或者数字
case "$Keypress" in
  [[:lower:]]   ) echo "Lowercase letter";;
  [[:upper:]]   ) echo "Uppercase letter";;
  [0-9]         ) echo "Digit";;
  * ) echo "Punctuation, whitespace, or other";;
esac
exit 0
EOF

# --- Demo 10 ---
cat > demo10.sh << 'EOF'
#!/bin/bash
script_name=`basename $0`
echo "The name of this script is $script_name."
textfile_listing=`ls *`
# 变量中包含了当前工作目录下所有的*文件
echo $textfile_listing
EOF

# --- 统一设置权限 ---
echo "正在创建文件并设置权限..."
chmod +x demo1.sh demo2.sh demo3.sh demo4.sh demo5.sh demo6.sh demo7.sh demo8.sh demo9.sh demo10.sh

echo "======================================"
echo "大功告成！文件 demo1.sh 到 demo10.sh 已生成。"
echo "您可以直接开始实验了。"
echo "======================================"
ls -l demo*.sh
