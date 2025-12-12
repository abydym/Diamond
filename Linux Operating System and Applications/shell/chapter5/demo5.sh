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
