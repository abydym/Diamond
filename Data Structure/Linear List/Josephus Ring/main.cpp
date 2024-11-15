#include <iostream>
using namespace std;
typedef struct Node {
    int data;
    struct Node *next;
}Node,*next;

Node *CreateList(int n) {
    int i;
    Node *head,*ptr,*r;
    head=(Node*)malloc(sizeof(Node));
    if(!head)
    {
        printf("Memory failed\n");
        return 0;
    }
    head->data=1;
    head->next=NULL;

    ptr=head;
    for(i=2;i<=n;i++)
    {
        r=(Node*)malloc(sizeof(Node));
        r->data=i;
        r->next=NULL;
        ptr->next=r;
        ptr=r;
    }
    ptr->next=head;
    ptr=head;
    return head;
}
void DeleteNode(Node* r,Node* p)
{
    Node* q;

    q=r->next;
    r->next=p;

    delete q;

}
void Josephus(int n,int m)
{
    int i,j;
    Node *head,*ptr,*r;

    head=CreateList(n);

    ptr=head;

    for(i=0;i<n-1;i++)
    {
        for(j=0;j<m-1;j++)
        {
            r=ptr;
            ptr=ptr->next;
        }

        cout<<"The No."<<ptr->data<<" person is out"<<endl;

        ptr=ptr->next;
        DeleteNode(r,ptr);
    }

        cout<<"Finally,the No."<<ptr->data<<" person remains!"<<endl;
}
int main()
{
    int n,m;
    cout<<"Please enter the total number of people and the number of deaths separately, for example: 10 3"<<endl;
    cin>>n>>m;
    Josephus(n,m);
    return 0;
}