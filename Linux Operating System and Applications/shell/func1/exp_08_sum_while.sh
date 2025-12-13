#!/bin/bash
# 题目要求：while循环求1到100的和

total=0
num=0

while ((num <= 100))
do
   # expr 是比较老的写法，但在实验中很常见
   total=`expr $total + $num`
   ((num+=1))
done

echo "The result (While) is $total"
