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
