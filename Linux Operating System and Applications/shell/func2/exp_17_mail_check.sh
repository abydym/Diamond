#!/bin/bash
# 题目要求：每隔5分钟检查是否有新邮件 (通过文件大小变化判断)

# 注意：为了方便实验，我们不检测真实的 /var/mail/cg
# 而是检测当前目录下的一个 dummy_mail 文件
# 你可以通过另一个终端向这个文件写入数据来测试： echo "new mail" >> dummy_mail

MAIL_FILE="./dummy_mail"
touch "$MAIL_FILE" # 确保文件存在

echo "开始监控邮件文件: $MAIL_FILE"
echo "提示：打开另一个终端输入 'date >> dummy_mail' 来模拟收到邮件"

# 获取初始大小 ($5 是 ls -l 输出的第五列：文件大小)
count1=`ls -l $MAIL_FILE | awk '{print $5}'`
echo "当前初始大小: $count1 字节"

while true
do
    echo "正在休眠 10秒..."
    sleep 10
    
    # 获取现在的大小
    count2=`ls -l $MAIL_FILE | awk '{print $5}'`
    
    if [ "$count1" -ne "$count2" ]; then
        echo "[提醒] 您有新的邮件！(文件大小从 $count1 变为 $count2)"
        # 更新基准大小
        count1=$count2
    else
        echo "没有新邮件..."
    fi
done
