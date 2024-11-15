#include <iostream>
#include <cstring>
using namespace std;
typedef struct
{
	char name[10];
	int id;
	char birth[15];
	char hobby[10];
	int room_id;
 } Student;

 typedef struct
 {
 	Student students[15];
 	int size;
 }StudentList;

void LoadFromFile(StudentList *list,const char *filename)
{
	FILE *fp=fopen(filename,"r");

	if (!fp)
	{
		cout<<"Fail to open this file"<<endl;
    	return;
	}

	list->size=0;

	while(fscanf(fp,"%s %d %s %s %d",list->students[list->size].name,
								&list->students[list->size].id,
								list->students[list->size].birth,
								list->students[list->size].hobby,
								&list->students[list->size].room_id)!=EOF)
	{
		list->size++;
	}

	fclose(fp);
}


void FindByRoom_ID(StudentList list,int room_id)
{
	int i;

	for(i=0;i<list.size;i++)
	{
		if(list.students[i].room_id==room_id)
		{
			cout<<"Name\tID\t\tBirth\t\tHobby\tRoom_ID"<<endl;
			cout<<list.students[i].name<<"\t"<<list.students[i].id<<"\t"<<list.students[i].birth<<"\t"<<list.students[i].hobby<<"\t"<<list.students[i].room_id<<"\n";
		}
	 }

	 cout<<endl;
}
void FindByID(StudentList list,int id)
{
	int i;

	for(i=0;i<list.size;i++)
	{
		if(list.students[i].id==id)
		{
			cout<<"Name\tBirth\t\tHobby"<<endl<<list.students[i].name<<"\t"<<list.students[i].birth<<"\t"<<list.students[i].hobby<<endl;
			break;
		}
	}

	if(i>=list.size)
	{
		cout<<"Fail to find"<<endl;
	}
}


void InsertRecord(StudentList *list)
{
	char name[10];
	int id;
	char birth[10];
	char hobby[10];
	int room_id;
	int i = 0;

	cin>>name>>id>>birth>>hobby>>room_id;

	while(i!=list->size)
	{
		i++;
	}

	strcpy(list->students[i].name,name);
	list->students[i].id=id;
	strcpy(list->students[i].birth,birth);
	strcpy(list->students[i].hobby,hobby);
	list->students[i].room_id=room_id;
	list->size++;
}

void DisplayList(StudentList list)
{
	int i;

	cout<<"Name\tID\t\tBirth\t\tHobby\tRoom_ID"<<endl;

	for(i=0;i<list.size;i++)
	{
		cout<<list.students[i].name<<"\t"<<list.students[i].id<<"\t"<<list.students[i].birth<<"\t"<<list.students[i].hobby<<"\t"<<list.students[i].room_id<<"\n";
	}

	cout<<endl;
}

void DeleteByID(StudentList *list,int id)
{
	int i=0;

	while(list->students[i].id!=id)
	{
		i++;
	}

	for(;i<list->size;i++)
	{
		list->students[i]=list->students[i+1];
	}

	list->size--;
}

void UpSortByID(StudentList list)
{
	Student temp;
	int i,j;

	for(i=0;i<list.size-1;i++)
	{
		for(j=0;j<list.size-i-1;j++)
		{
			if(list.students[j].id>list.students[j+1].id)
			{
				temp=list.students[j];
				list.students[j]=list.students[j+1];
				list.students[j+1]=temp;
			}
		}
	}

	DisplayList(list);
}

void UpSortByRoom_ID(StudentList list)
{
	Student temp;
	int i,j;

	for(i=0;i<list.size-1;i++)
	{
		for(j=0;j<list.size-i-1;j++)
		{
			if(list.students[j].room_id>list.students[j+1].room_id)
			{
				temp=list.students[j];
				list.students[j]=list.students[j+1];
				list.students[j+1]=temp;
			}
		}
	}

	DisplayList(list);
}

int main()
{
	StudentList list;
	int id,choice,flag=0;

	LoadFromFile(&list,"list.txt");
	while(choice)
	{
		cout<<"Please choose the operation you want"<<endl;
		cout<<"1.Find by your ID"<<endl;
		cout<<"2.Find by your ID of dorm"<<endl;
		cout<<"3.Delete by ID"<<endl;
		cout<<"4.Insert a record"<<endl;
		cout<<"5.Print students lists"<<endl;
		cout<<"6.Print students lists by ID"<<endl;
		cout<<"7.Print students lists by ID of dorm"<<endl;
		cout<<"0.exit"<<endl;
		cin>>choice;

        switch (choice)
		{
            case 1:
                cout<<"Enter ID: ";
                cin>>id;
                FindByID(list, id);
                break;
            case 2:
                cout<<"Enter ID of dorm: ";
				cin>>id;
                FindByRoom_ID(list, id);
                break;
            case 3:
                cout<<"Enter ID to delete: ";
                cin>>id;
                DeleteByID(&list, id);
                break;
            case 4:
                InsertRecord(&list);
                break;
			case 5:
				DisplayList(list);
				break;
            case 6:
                UpSortByID(list);
                break;
            case 7:
            	UpSortByRoom_ID(list);
            	break;
            case 0:
                break;
            default:
                cout<<"Invalid choice"<<endl;
    	}

	}

	return 0;
}
