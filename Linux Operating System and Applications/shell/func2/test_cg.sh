#!/bin/sh
gdialog --title "Questionnaire" --yesno "Will you participate in this survey?" 9 18
if( $? != 0 ); then
        gdialog --infobox " Thank you "
        sleep 1
        gdialog --clear
        exit 0
fi
gdialog --title "Questionnaire" --msgbox "This is a survey about your personal information" 9 18
gdialog --title "Questionnaire" --inputbox "Enter your name" 9 18 2>name.txt
_name=$(cat name.txt)
gdialog --menu "$_name, what is your major?" 9 18 3 1 "Liberal Art" 2 "Science"
3 "Computer Science" 2>choice.txt
_choice=$(cat choice.txt)
case "$_choice" in
        1) gdialog --title "Questionnaire" --msgbox "Good choice" 9 18 ;;
        2) gdialog --title "Questionnaire" --msgbox "Excellent" 9 18 ;;
        *) gdialog --title "Questionnaire" --checklist "Choose the lanuage you learned"  9 18 5 1 "C" "off" 2 "C++" "off" 3 "Java" "off" 4 "Ruby" "off" 5 "Delpi" "off";;
esac
 
sleep 1
gdialog --clear
exit 0
