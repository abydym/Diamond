#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>
#include <graphics.h>
#include <conio.h>
#define MAXSIZE 100
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                            //
// Preface: This is my first major assignment on data structures.                                                             //
// I want to express my gratitude to my class teacher, Mr. Ye,                                                                //
// for giving me useful suggestions, extending the deadline twice, giving me enough time to patch up this assignment.         //
// It's quite strange to say, but I originally thought it was impossible for me to complete it.                               //
// However, I didn't expect to barely meet the requirements of the assignment during the process of patching things up.       //
// I was planning to submit an interface with just a plain black box, but on the night before the deadline,                   //
// I had a sudden inspiration and decided to try using my limited knowledge of EasyX to create a simple graphical interface.  //
// This can be considered a more unique black box, right? Hahaha.                                                             //
// The functionality of this is definitely not as good as the pure black box,                                                 //
// but in a way, it's also a step beyond myself!                                                                              //
//                                                                                                                            //
//                                                                                                                            //
//  Written by abydym                                                                                                         //
//  2024.10.20                                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Medal {
    int rank;
    string country;
    int gold;
    int silver;
    int bronze;
    int total;
};
typedef struct{
    Medal *elem;
    int length;
} SeqList;


int InitList(SeqList &L){
    L.elem = new Medal[MAXSIZE];
    if(!L.elem){
        exit(-1);
    }
    L.length = 0;
    return 1;
}

void FindByRank(SeqList L,int r) {
if(r>0&&r<=L.length) {
    cout<<"Name\tGold\tSilver\tBronze"<<endl;
    cout<<L.elem[r-1].country<<L.elem[r-1].gold<<L.elem[r-1].silver<<L.elem[r-1].bronze<<endl;
}
    else {
        cout<<"An error occured during the process of finding value by rank"<<endl;
    }
}

void FindByName(SeqList L,string country) {
    int i = 0;
    while(i<L.length) {
        i++;
    }
    if(i>=L.length) {
        cout<<"An error occured during the process of finding by name"<<endl;
    }
    else {
        cout<<"Rank:"<<L.elem[i].rank<<endl;
    }
}
int GetElem(SeqList L,int i,Medal &e){
    //i是指第几个元素
    if(i<1 || i>L.length){
        return -2;
    }
    e = L.elem[i - 1];
    return 1;
}

int LocElem(SeqList L, string e){
    int i;
    for(i=0;i<L.length;i++){
        if(L.elem[i].country==e){ //注意此处gold和传参时的int类型要一致，否则会报错
            return i + 1;
        }

    }
    return 0;
}
void DeleteCountryByRank(SeqList &L) {
    int rank;
    cout << "Enter the rank to delete the country's medal information: ";
    cin >> rank;

    bool found = false;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i].rank == rank) {
            found = true;
            // 删除元素
            for (int j = i; j < L.length - 1; j++) {
                L.elem[j] = L.elem[j + 1];
            }
            L.length--;
            cout << "Country with rank " << rank << " has been deleted." << endl;

            // 重新设置排名
            int currentRank = 1;
            for (int j = 0; j < L.length; ++j) {
                if (j == 0 || (L.elem[j].gold != L.elem[j - 1].gold ||
                               L.elem[j].silver != L.elem[j - 1].silver ||
                               L.elem[j].bronze != L.elem[j - 1].bronze ||
                               L.elem[j].total != L.elem[j - 1].total)) {
                    currentRank = j + 1;
                               }
                L.elem[j].rank = currentRank;
            }
            break;
        }
    }

    if (!found) {
        cout << "No country found with rank " << rank << "." << endl;
    }
}

void PrintMedalTable(SeqList L) {
    if (L.length == 0) {
        cout << "No data to print." << endl;
        return;
    }

    // 打印表头
    cout << left << setw(5) << "Rank"
         << left << setw(20) << "Country"
         << left << setw(5) << "Gold"
         << left << setw(5) << "Silver"
         << left << setw(5) << "Bronze"
         << left << setw(5) << "Total"
         << endl;

    // 打印每一条记录
    for (int i = 0; i < L.length; i++) {
        cout << left << setw(5) << L.elem[i].rank
             << left << setw(20) << L.elem[i].country
             << left << setw(5) << L.elem[i].gold
             << left << setw(5) << L.elem[i].silver
             << left << setw(5) << L.elem[i].bronze
             << left << setw(5) << L.elem[i].total
             << endl;
    }
}
bool compareMedals(const Medal &a, const Medal &b) {
    if (a.gold != b.gold) return a.gold > b.gold;
    if (a.silver != b.silver) return a.silver > b.silver;
    if (a.bronze != b.bronze) return a.bronze > b.bronze;
    return a.total > b.total;
}
void GetMedalInfoByRank(SeqList L) {
    int rank;
    cout << "Enter the rank to get the medal information: ";
    cin >> rank;

    bool found = false;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i].rank == rank) {
            found = true;
            cout << left << setw(5) << "Rank"
                 << left << setw(20) << "Country"
                 << left << setw(5) << "Gold"
                 << left << setw(5) << "Silver"
                 << left << setw(5) << "Bronze"
                 << left << setw(5) << "Total"
                 << endl;
            cout << left << setw(5) << L.elem[i].rank
                 << left << setw(20) << L.elem[i].country
                 << left << setw(5) << L.elem[i].gold
                 << left << setw(5) << L.elem[i].silver
                 << left << setw(5) << L.elem[i].bronze
                 << left << setw(5) << L.elem[i].total
                 << endl;
            break;
        }
    }
}

void GetRankByCountry(SeqList L) {
    string country;
    cout << "Enter the country name to get its rank: ";
    cin >> country;

    bool found = false;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i].country == country) {
            found = true;
            cout << "Country: " << L.elem[i].country
                 << " Rank: " << L.elem[i].rank << endl;
            break;
        }
    }

    if (!found) {
        cout << "No country found with name " << country << "." << endl;
    }
}

void InsertMedalRecord(SeqList &L) {
    Medal newRecord;
    cout << "Enter the country name: ";
    cin >> newRecord.country;
    cout << "Enter the number of gold medals: ";
    cin >> newRecord.gold;
    cout << "Enter the number of silver medals: ";
    cin >> newRecord.silver;
    cout << "Enter the number of bronze medals: ";
    cin >> newRecord.bronze;
    newRecord.total = newRecord.gold + newRecord.silver + newRecord.bronze;

    // 插入新记录
    L.elem[L.length] = newRecord;
    L.length++;

    // 重新排序
    sort(L.elem, L.elem + L.length, [](const Medal &a, const Medal &b) {
        if (a.total != b.total) return a.total > b.total;
        if (a.gold != b.gold) return a.gold > b.gold;
        if (a.silver != b.silver) return a.silver > b.silver;
        return a.bronze > b.bronze;
    });

    // 重新设置排名
    int currentRank = 1;
    for (int i = 0; i < L.length; ++i) {
        if (i == 0 || (L.elem[i].gold != L.elem[i - 1].gold ||
                       L.elem[i].silver != L.elem[i - 1].silver ||
                       L.elem[i].bronze != L.elem[i - 1].bronze ||
                       L.elem[i].total != L.elem[i - 1].total)) {
            currentRank = i + 1;
                       }
        L.elem[i].rank = currentRank;
    }

    cout << "New record inserted and medal table sorted." << endl;
}

int main() {
    initgraph(720, 720);

    SeqList L;
    int choose = -1;
    int i=0,temp;
    Medal e;

    string head_country, line;

    int head_gold, head_silver, head_bronze;

    while(1){
        cleardevice();
        settextstyle(20,0,_T("Times New Roman"));
        outtextxy(10, 10, _T("1. Setup"));
        outtextxy(10, 40, _T("2. Input File"));
        outtextxy(10, 70, _T("3. Print Medal Table"));
        outtextxy(10, 100, _T("4. Get Medal Information by Rank"));
        outtextxy(10, 130, _T("5. Get Rank by Country"));
        outtextxy(10, 160, _T("6. Delete Country by Rank"));
        outtextxy(10, 190, _T("7. Insert New Record"));
        outtextxy(10, 220, _T("0. Exit"));
        outtextxy(180, 700, _T("Please press shift first and then enter the number."));
        // cout<<"1.Setup"<<endl;
        // cout<<"2.Input File"<<endl;
        // cout<<"3.Print Medal Table"<<endl;
        // cout<<"4.Get Medal Information by Rank"<<endl;
        // cout<<"5.Get Rank by Country"<<endl;
        // cout<<"6.Delete Country by Rank"<<endl;
        // cout<<"7.Insert New Record"<<endl;
        // cout<<"0.exit"<<endl;
        // cout<<"Please select the operation you want"<<endl;
        // cin>>choose;
        char ch = getch();
        choose = ch - '0'; // 这行代码的作用是把字符转换为整数，其中的0必须要用单引号，否则会提示“不能将二元operator-应用于char和const char *(转换自const char[1])”
        switch(choose){
            default:
                outtextxy(10, 250, _T("Invalid choice, please try again."));
                Sleep(1000);
                // cout<<"Invalid choice, please try again."<<endl;
                break;
            case 1:
                if(InitList(L))
                    outtextxy(10, 250, _T("Success!"));
                    // cout<<"Success!"<<endl;
                else
                    outtextxy(10, 250, _T("An error occurred during the process of establishing the sequential list"));
                Sleep(1000);
                    // cout<<"An error occured during the process of establishing the sequential list"<<endl;
                break;
            case 3:
                PrintMedalTable(L);
                break;
            case 4:
                outtextxy(10, 250, _T("Entering case 4: Get Medal Info by Rank"));
                GetMedalInfoByRank(L);
                outtextxy(10, 280, _T("Exiting case 4: Get Medal Info by Rank"));
                Sleep(1000);   
                break;
                // cout<<"Entering case 4: Get Medal Info by Rank"<<endl;
                // GetMedalInfoByRank(L);
                // cout<<"Exiting case 4: Get Medal Info by Rank"<<endl;
                break;
            case 5:
                outtextxy(10, 250, _T("Entering case 5: Get Rank by Country"));
                GetRankByCountry(L);
                outtextxy(10, 280, _T("Exiting case 5: Get Rank by Country"));
                Sleep(1000);   
                break;
                // cout<<"Entering case 5: Get Rank by Country"<<endl;
                // GetRankByCountry(L);
                // cout<<"Exiting case 5: Get Rank by Country"<<endl;
                break;
            case 6:
                outtextxy(10, 250, _T("Entering case 6: Delete Country by Rank"));
                DeleteCountryByRank(L);
                outtextxy(10, 280, _T("Exiting case 6: Delete Country by Rank"));
                Sleep(1000);   
                break;
                // cout<<"Entering case 6: Delete Country by Rank"<<endl;
                // DeleteCountryByRank(L);
                // cout<<"Exiting case 6: Delete Country by Rank"<<endl;
                break;
            case 7:
                outtextxy(10, 250, _T("Entering case 7: Insert New Record"));
                InsertMedalRecord(L);
                outtextxy(10, 280, _T("Exiting case 7: Insert New Record"));
                Sleep(1000);   
                // cout<<"Entering case 7: Insert New Record"<<endl;
                // InsertMedalRecord(L);
                // cout<<"Exiting case 7: Insert New Record"<<endl;
                break;
            case 0:
                outtextxy(10, 250, _T("Exiting..."));
                Sleep(1000);   
                closegraph();  // 关闭绘图窗口
                // cout<<"Exiting..."<<endl;
                return 0;
            case 2:
                L.elem = new Medal[MAXSIZE];
                if(!L.elem){
                    outtextxy(10, 250, _T("Memory allocation failed"));
                    Sleep(1000);   
                exit(-1);
            }
                L.length = 0;
                fstream file;
                file.open("Medal.csv");
                if(!file){
                    outtextxy(10, 250, _T("An error occurred during the process of opening the file 'Medal.csv'"));
                    Sleep(1000);   
                // cout<<"An error occured during the process of opening the file'Medal.csv'"<<endl;
                exit(-2);
            }
                string line;
                getline(file, line);
                outtextxy(10, 250, _T("Header line: "));
                outtextxy(10, 280, line.c_str());
                // cout << "Header line: " << line << endl;

            while(getline(file, line)) {
                outtextxy(10, 310, _T("Processing line: "));
                outtextxy(10, 340, line.c_str());
                // cout << "Processing line: " << line << endl;
                stringstream ss(line);
                string field;
                vector<string> fields;

                while (getline(ss, field, ',')) {
                    fields.push_back(field);
                    // cout << "Field: " << field << endl;
                    outtextxy(10, 370, _T("Field: "));
                    outtextxy(10, 400, field.c_str());
                }

                if (fields.size() == 5) {
                    try {
                        L.elem[L.length].rank = L.length + 1;
                        L.elem[L.length].country = fields[0];
                        L.elem[L.length].gold = stoi(fields[1]);
                        L.elem[L.length].silver = stoi(fields[2]);
                        L.elem[L.length].bronze = stoi(fields[3]);
                        L.elem[L.length].total = stoi(fields[4]);
                        L.length++;
                        outtextxy(10, 430, _T("Added record: "));
                        outtextxy(10, 460, (L.elem[L.length - 1].country + " (" +
                                             to_string(L.elem[L.length - 1].gold) + ", " +
                                             to_string(L.elem[L.length - 1].silver) + ", " +
                                             to_string(L.elem[L.length - 1].bronze) + ", " +
                                             to_string(L.elem[L.length - 1].total) + ")").c_str());
                    } catch (const exception& e) {
                        outtextxy(10, 430, _T("Error converting fields: "));
                        outtextxy(10, 460, e.what());
                    }
                } else {
                    outtextxy(10, 430, _T("Skipping invalid line: "));
                    outtextxy(10, 460, line.c_str());
                }
                //         cout << "Added record: " << L.elem[L.length - 1].country << " ("
                //              << L.elem[L.length - 1].gold << ", "
                //              << L.elem[L.length - 1].silver << ", "
                //              << L.elem[L.length - 1].bronze << ", "
                //              << L.elem[L.length - 1].total << ")" << endl;
                //     } catch (const exception& e) {
                //         cout << "Error converting fields: " << e.what() << endl;
                //     }
                // } else {
                //     cout << "Skipping invalid line: " << line << endl;
                // }
            }

            // 排序
            sort(L.elem, L.elem + L.length, compareMedals);

            // 重新设置排名
            int currentRank = 1;
            for (int i = 0; i < L.length; ++i) {
                if (i == 0 || (L.elem[i].gold != L.elem[i - 1].gold ||
                               L.elem[i].silver != L.elem[i - 1].silver ||
                               L.elem[i].bronze != L.elem[i - 1].bronze ||
                               L.elem[i].total != L.elem[i - 1].total)) {
                    currentRank = i + 1;
                               }
                L.elem[i].rank = currentRank;
            }
            // cout << "Success! Total records: " << L.length << endl;
            outtextxy(10, 490, _T("Success! Total records: "));
            outtextxy(10, 520, to_string(L.length).c_str());
            file.close();
            Sleep(5000);   
            break;

            // file>>head_country>>head_gold>>head_silver>>head_bronze;
            // while(!file.eof()){
            //     file>>L.elem[i].country>>L.elem[i].gold>>L.elem[i].silver>>L.elem[i].bronze;
            //     i++;
            // }
            // cout<<"Success!"<<endl;
            // L.length = i;
            // file.close();
            // PrintMedalTable(L);
            // break;

            //             case 3:
            //                 cout<<"Please input a location to get value"<<endl;
            //                 cin>>i;
            //                 temp = GetElem(L,i,e);
            //                 if(temp != 0) {
            //                     cout<<"Success!"<<endl;
            //                     cout<<"The information of this country is:";
            //                     cout << left << setw(15) << e.gold << "\t" << left << setw(50)
            //                         << e.silver << "\t" << left << setw(5) << e.bronze << endl
            //                         << endl;
            //                 }
            //                 else
            //                     cout<<"An error occured during the process of geeting the value"<<endl;
            //                 break;
            //
            //             case 4:
            //                 cout<<"Please input the country name to search:";
            //
        }
    }
    //
    //
    //
    return 0;
}


