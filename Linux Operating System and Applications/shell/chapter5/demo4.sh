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
