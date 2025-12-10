#!/bin/bash
read Keypress  #在终端输入一个字符或者数字
case "$Keypress" in
  [[:lower:]]   ) echo "Lowercase letter";;
  [[:upper:]]   ) echo "Uppercase letter";;
  [0-9]         ) echo "Digit";;
  * ) echo "Punctuation, whitespace, or other";;
esac
exit 0
