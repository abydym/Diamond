#!/bin/bash

echo "正在生成最后一部分实验脚本..."

# --- (1) 文件删除菜单管理 ---
cat > exp_14_delete_menu.sh << 'EOF'
#!/bin/bash
# 题目要求：输入路径，提供菜单：删除特定类型、删除除某文件外的文件、删除所有、退出

echo "--- 文件清理助手 ---"
read -p "请输入目标目录路径: " target_dir

if [ ! -d "$target_dir" ]; then
    echo "错误：目录不存在！"
    exit 1
fi

cd "$target_dir" || exit

while true; do
    echo "---------------------------"
    echo "当前目录: $(pwd)"
    echo "1. 删除指定后缀的文件 (例如删除所有 .txt)"
    echo "2. 删除目录或文件 (指定名称)"
    echo "3. 删除某文件外的其他所有文件 (保留一个)"
    echo "4. 删除当前目录下所有文件 (清空)"
    echo "5. 退出"
    echo "---------------------------"
    read -p "请选择操作 (1-5): " choice

    case "$choice" in
        1)
            read -p "请输入要删除的文件后缀 (如 txt): " ext
            # 确认一下，防止误删
            read -p "确定删除所有 .$ext 文件吗? (y/n): " confirm
            if [ "$confirm" == "y" ]; then
                rm *."$ext" 2>/dev/null
                echo "删除完成。"
            fi
            ;;
        2)
            read -p "请输入要删除的文件或文件夹名: " name
            rm -rf "$name"
            echo "已删除 $name"
            ;;
        3)
            read -p "请输入要【保留】的文件名: " keep_file
            if [ -e "$keep_file" ]; then
                # 使用 find 命令查找不是该文件的项目并删除
                # -maxdepth 1 保证只操作当前层级
                find . -maxdepth 1 ! -name "$keep_file" ! -name "." -exec rm -rf {} +
                echo "已删除除 $keep_file 外的所有文件。"
            else
                echo "错误：当前目录下找不到 $keep_file"
            fi
            ;;
        4)
            read -p "警告：确定清空当前目录所有内容吗？(y/n): " confirm
            if [ "$confirm" == "y" ]; then
                rm -rf ./*
                echo "目录已清空。"
            fi
            ;;
        5)
            echo "退出程序。"
            break
            ;;
        *)
            echo "无效输入。"
            ;;
    esac
done
EOF

# --- (2) 递归遍历目录 (ls -R 模拟) ---
cat > exp_15_recursive_list.sh << 'EOF'
#!/bin/bash
# 题目要求：补全程序，实现 ls -R 功能 (递归遍历子目录)

# 定义 list 函数
list(){
    local current_dir=$1
    
    # 切换到目标目录，如果失败则返回
    cd "$current_dir" || return
    
    echo ""
    echo "Directory: $current_dir"
    echo "-----------------------"
    ls -l | grep "^-"  # 先显示当前目录下的文件

    # 遍历当前目录下的所有项
    for i in *
    do 
        # 如果是目录，且不是 . 或 ..
        if [ -d "$i" ]; then
             full_path="$current_dir/$i"
             echo "-> Found subdirectory: $full_path"
             
             # 【递归调用】核心点
             list "$full_path"
             
             # 递归返回后，必须切回当前目录，否则后续循环会出错
             cd "$current_dir"
        fi 
    done 
}

# 主程序开始
read -p "请输入要遍历的目录 (绝对路径): " start_dir

if [ -d "$start_dir" ]; then
    echo "开始遍历..."
    list "$start_dir"
else
    echo "目录不存在"
fi
EOF

# --- (3) 纸牌比大小游戏 ---
cat > exp_16_card_game.sh << 'EOF'
#!/bin/bash
# 题目要求：扑克牌抽牌比大小游戏
# 修复了原文中的语法错误

# 1. 初始化牌堆 (ok数组标记牌是否被抽过，1代表在牌堆中)
for i in $(seq 1 54)
do
    ok[$i]=1
done

max=0 # 记录当前最大的点数
num=0 # 记录赢家是谁

# 2. 游戏开始，4个玩家
for i in $(seq 1 4)
do
    echo "----------------"
    echo "Player $i 抽牌中..."
    
    # 随机抽一张牌 (1-53)
    # 原题逻辑是 RANDOM%53+1，这意味着很难抽到 54(大王)，我们尊重原题逻辑
    a=$((RANDOM%53+1))
    
    # 如果这张牌已经被抽过了(ok[a]==0)，就重抽
    while [[ ${ok[$a]} -eq 0 ]]; do
        a=$((RANDOM%53+1))
    done
    
    # 标记这张牌已被抽走
    ok[$a]=0
    
    # 比较大小，记录最大值
    if [ $a -gt $max ]; then
        max=$a
        num=$i
    fi

    # 计算花色 (0-3)
    HuaSe=$((a%4))
    case $HuaSe in
        0) HS='梅花(Club)';;
        1) HS='方块(Diamond)';;
        2) HS='红心(Heart)';;
        3) HS='黑桃(Spade)';;
    esac

    # 计算牌面大小
    DaXiao=$((a/4+1))
    
    # 显示牌面
    case $DaXiao in
        2|3|4|5|6|7|8|9|10) echo "抽到了: $HS $DaXiao";;
        11) echo "抽到了: $HS J";;
        12) echo "抽到了: $HS Q";;
        13) echo "抽到了: $HS K";;
        1)  echo "抽到了: $HS A";;
        14) echo "抽到了: 小王 (Small Joker)";;
        15) echo "抽到了: 大王 (Big Joker)";;
        *)  echo "未知牌型";;
    esac
    
    # 原题这里有个 read ll 暂停，为了流畅我注释掉了，或者保留
    # read -p "按回车继续..." ll
done

echo "======================"
echo "最终赢家是: Player $num !"
echo "======================"
EOF

# --- (4) 邮件监控程序 ---
cat > exp_17_mail_check.sh << 'EOF'
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
    echo "正在休眠 10秒 (原题5分钟，为方便测试改为10秒)..."
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
EOF

# --- (5) GUI 问卷调查 (仿写) ---
cat > exp_18_gui_survey.sh << 'EOF'
#!/bin/bash
# 题目要求：仿照 gdialog 程序编写问卷
# 注意：现代 Linux 通常使用 whiptail 或 dialog 替代古老的 gdialog
# 这里使用 whiptail 重写，功能一致

# 1. 询问是否参与
whiptail --title "问卷调查" --yesno "你愿意参与这个关于编程的调查吗?" 10 60
if [ $? -ne 0 ]; then
    whiptail --title "提示" --msgbox "好吧，谢谢。" 10 60
    exit 0
fi

# 2. 说明信息
whiptail --title "问卷调查" --msgbox "这是一个关于你编程喜好的调查。" 10 60

# 3. 输入姓名 (结果输出到 stderr，重定向到文件)
whiptail --title "个人信息" --inputbox "请输入你的名字:" 10 60 3>&1 1>&2 2>&3 > name.txt
name=$(cat name.txt)

if [ -z "$name" ]; then name="无名氏"; fi

# 4. 选择专业 (菜单)
whiptail --title "专业选择" --menu "$name, 你的专业是?" 15 60 4 \
"1" "计算机科学 (CS)" \
"2" "软件工程 (SE)" \
"3" "网络工程 (Network)" \
"4" "其他" 3>&1 1>&2 2>&3 > choice.txt

choice=$(cat choice.txt)

# 5. 根据选择做出反应
case "$choice" in
    1|2) 
        whiptail --msgbox "太棒了，这是当下最热门的专业！" 10 60 
        ;;
    3) 
        whiptail --msgbox "网络技术非常重要！" 10 60 
        ;;
    *) 
        # 多选框 (Checklist)
        whiptail --title "技能调查" --checklist "请选择你掌握的语言 (空格选择):" 15 60 5 \
        "Bash" "Shell脚本" ON \
        "Python" "数据分析" OFF \
        "C" "底层开发" OFF \
        "Java" "企业开发" OFF \
        "HTML" "前端开发" OFF 3>&1 1>&2 2>&3 > languages.txt
        ;;
esac

whiptail --msgbox "感谢参与！再见。" 10 60
clear
echo "调查结束，临时文件 name.txt, choice.txt 已生成。"
EOF

# --- 权限设置 ---
chmod +x exp_*.sh
echo "生成完毕！请查看当前目录下的 exp_14 到 exp_18 脚本。"
ls -l exp_14*.sh exp_15*.sh exp_16*.sh exp_17*.sh exp_18*.sh
