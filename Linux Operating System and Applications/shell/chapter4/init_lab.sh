#!/bin/bash

# --- Demo 1: if-else 判断 ---
cat > demo1.sh << 'EOF'
#!/bin/bash
a=10
b=20
if [ $a == $b ]
then
   echo "a 等于 b"
elif [ $a -gt $b ]
then
   echo "a 大于 b"
elif [ $a -lt $b ]
then
   echo "a 小于 b"
else
   echo "没有符合的条件"
fi
EOF

# --- Demo 2: test 命令 ---
cat > demo2.sh << 'EOF'
#!/bin/bash
num1=$[2*3]
num2=$[1+5]
if test $[num1] -eq $[num2]
then
    echo '两个数字相等!'
else
    echo '两个数字不相等!'
fi
EOF

# --- Demo 3: for 循环 (数字列表) ---
cat > demo3.sh << 'EOF'
#!/bin/bash
for loop in 1 2 3 4 5
do
    echo "The value is: $loop"
done
EOF

# --- Demo 4: for 循环 (字符串) ---
cat > demo4.sh << 'EOF'
#!/bin/bash
for str in 'This is a string'
do
    echo $str
done
EOF

# --- Demo 5: while 循环 (基本) ---
cat > demo5.sh << 'EOF'
#!/bin/bash
int=1
while(( $int<=5 ))
do
    echo $int
    let "int++"
done
echo $int
EOF

# --- Demo 6: while 循环 (读取输入) ---
cat > demo6.sh << 'EOF'
#!/bin/bash
echo '按下 <CTRL-D> 退出'
echo -n '输入你最喜欢的网站名: '
while read FILM
do
    echo "是的！$FILM 是一个好系统"
done
EOF

# --- Demo 7: 嵌套循环 ---
cat > demo7.sh << 'EOF'
#!/bin/bash
outer=1             # 设置外部循环计数.
# 开始外部循环.
for a in 1 2 3 4 5
do
  echo "Pass $outer in outer loop."
  echo "---------------------"
  inner=1           # 重设内部循环的计数.
  # ===============================================
  # 开始内部循环.
  for b in 1 2 3 4 5
  do
    echo "Pass $inner in inner loop."
    let "inner+=1"  # 增加内部循环计数.
  done
  # 内部循环结束.
  # ===============================================
  let "outer+=1"    # 增加外部循环的计数.
  echo              # 每次外部循环之间的间隔.
done               # 外部循环结束.
exit 0
EOF

# --- Demo 8: until 循环 ---
cat > demo8.sh << 'EOF'
#!/bin/bash
a=0
until [ ! $a -lt 10 ]
do
   echo $a
   a=`expr $a + 1`
done
EOF

# --- Demo 9: case 语句 (基本) ---
cat > demo9.sh << 'EOF'
#!/bin/bash
echo '输入 1 到 4 之间的数字:'
echo '你输入的数字为:'
read aNum
case $aNum in
    1)  echo '你选择了 1'
    ;;
    2)  echo '你选择了 2'
    ;;
    3)  echo '你选择了 3'
    ;;
    4)  echo '你选择了 4'
    ;;
    *)  echo '你没有输入 1 到 4 之间的数字'
    ;;
esac
EOF

# --- Demo 10: break 跳出循环 ---
cat > demo10.sh << 'EOF'
#!/bin/bash
while :
do
    echo -n "输入 1 到 5 之间的数字:"
    read aNum
    case $aNum in
        1|2|3|4|5) echo "你输入的数字为 $aNum!"
        ;;
        *) echo "你输入的数字不是 1 到 5 之间的! 游戏结束"
            break
        ;;
    esac
done
EOF

# --- Demo 11: continue 跳过本次循环 ---
cat > demo11.sh << 'EOF'
#!/bin/bash
while :
do
    echo -n "输入 1 到 5 之间的数字: "
    read aNum
    case $aNum in
        1|2|3|4|5) echo "你输入的数字为 $aNum!"
        ;;
        *) echo "你输入的数字不是 1 到 5 之间的!"
            continue
            echo "游戏结束"
        ;;
    esac
done
EOF

# --- Demo 12: case 语句 (字符串匹配) ---
cat > demo12.sh << 'EOF'
#!/bin/bash
site="cg"
case "$site" in
"cg") echo "cg教学平台"
;;
"google") echo "Google 搜索"
;;
"taobao") echo "淘宝网"
;;
esac
EOF

# --- 统一设置权限 ---
echo "正在创建文件并设置权限..."
chmod +x demo1.sh demo2.sh demo3.sh demo4.sh demo5.sh demo6.sh demo7.sh demo8.sh demo9.sh demo10.sh demo11.sh demo12.sh

echo "================================================="
echo "任务完成！已生成 demo1.sh 到 demo12.sh (共12个文件)"
echo "您可以直接开始执行了。"
echo "================================================="
ls -l demo*.sh
