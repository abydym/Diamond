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
