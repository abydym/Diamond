#!/bin/bash
# systeminfo.sh - 显示当前主机系统信息
echo "-----------------------------------------"
echo "            主机系统信息概览"
echo "-----------------------------------------"

echo "主机名:		$(hostname)"
echo "IPv4地址:		$(hostname -I | awk '{print $1}')"
source /etc/os-release
echo "操作系统:		$PRETTY_NAME"
echo "内核版本:		$(uname -r)"
echo "CPU型号:		$(lscpu | grep "Model name" | awk -F: '{print $2}' | sed 's/^[ \t]*//')"
echo "内存大小:		$(free -h | grep Mem | awk '{print $2}')"
echo "硬盘大小:		$(lsblk -d -o NAME,SIZE,TYPE | grep disk | awk '{print $2}' | tr '\n' ' ')"
echo ""
echo "---------------------------------"
