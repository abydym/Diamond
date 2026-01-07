#!/bin/bash

USER_LINE=$(grep "$1" /etc/passwd)

if [ -n "$USER_LINE" ]; then
	echo" 监控系统：发现用户 $USER_LINE 正在系统内。"
else
	echo "警告：未找到该用户！"
fi
