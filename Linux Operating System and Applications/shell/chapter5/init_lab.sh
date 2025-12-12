#!/bin/bash

# 1. 准备目录 chapter5
mkdir -p chapter5

# --- Demo 1: 函数的基本定义与调用 ---
cat > chapter5/demo1.sh << 'EOF'
#!/bin/bash
# 定义函数
demoFun(){
    echo "这是我的第一个 shell 函数!"
}

echo "-----函数开始执行-----"
# 调用函数
demoFun
echo "-----函数执行完毕-----"
EOF

# --- Demo 2: 带返回值的函数 (return) ---
cat > chapter5/demo2.sh << 'EOF'
#!/bin/bash
funWithReturn(){
    echo "这个函数会对输入的两个数字进行相加运算..."
    echo "输入第一个数字: "
    read aNum
    echo "输入第二个数字: "
    read anotherNum
    echo "两个数字分别为 $aNum 和 $anotherNum !"
    # return 只能返回 0-255 的整数，通常用于返回状态码
    return $(($aNum+$anotherNum))
}

# 调用函数
funWithReturn

# 使用 $? 获取上一个函数的返回值
echo "输入的两个数字之和为 $? !"
EOF

# --- Demo 3: 函数参数传递 ($1, $2...) ---
cat > chapter5/demo3.sh << 'EOF'
#!/bin/bash
funWithParam(){
    echo "第一个参数为 $1 !"
    echo "第二个参数为 $2 !"
    # 注意：$10 会被解释为 $1 后面跟着字符 0
    echo "第十个参数为 $10 ! (错误写法)"
    # 正确写法是 ${10}
    echo "第十个参数为 ${10} ! (正确写法)"
    echo "第十一个参数为 ${11} !"
    echo "参数总数有 $# 个!"
    echo "作为一个字符串输出所有参数 $* !"
}

# 调用函数并传递大量参数
funWithParam 1 2 3 4 5 6 7 8 9 34 73
EOF

# --- Demo 4: 局部变量 (local) ---
cat > chapter5/demo4.sh << 'EOF'
#!/bin/bash
# 在函数内部的全局和局部变量.

func (){
  local loc_var=23       # 声明为局部变量.
  echo                   # 使用内建的'local'关键字.
  echo "\"loc_var\" in function = $loc_var"
  global_var=999         # 没有声明为局部变量.
                         # 默认为全局变量.
  echo "\"global_var\" in function = $global_var"
}

func

# 现在，来看看是否局部变量"loc_var"能否在函数外面可见.
echo "\"loc_var\" outside function = $loc_var"
# 结果应该是空的，因为 loc_var 是局部的

echo "\"global_var\" outside function = $global_var"
# 结果应该是 999，因为 global_var 是全局的

exit 0
EOF

# --- Demo 5: 变量作用域测试 ---
cat > chapter5/demo5.sh << 'EOF'
#!/bin/bash
func (){
  global_var=37    # 在函数还没有被调用前
                   # 变量只在函数内可见.
}

# 函数"func"还没有被调用, 所以变量$global_var还不能被访问.
echo "global_var = $global_var"

# 调用函数，执行赋值操作
func

# 已经在函数调用时设置了值，现在可以访问了
echo "global_var = $global_var"
EOF

# --- 统一设置权限 ---
echo "正在生成文件并设置权限..."
chmod +x chapter5/demo1.sh chapter5/demo2.sh chapter5/demo3.sh chapter5/demo4.sh chapter5/demo5.sh

echo "================================================="
echo "任务完成！所有函数实验脚本已生成在 chapter5 目录下："
ls -l chapter5/
echo "================================================="
