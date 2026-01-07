#!/bin/bash

HOSTNAME=$(hostname)
echo "——— 正在为 $HOSTNAME 执行系统巡检———"

ARCH=$(uname -a | grep -a "aarch64")

MEMORY_INFO=$(free -m | awk '{print $3}')

echo "——— 巡检报告 ———"
echo "主机名称： $HOSTNAME"
echo "系统架构： $ARCH"
echo "内存详细： $MEMORY_INFO"
