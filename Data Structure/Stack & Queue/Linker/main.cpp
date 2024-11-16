#include <iostream>

using namespace std;
typedef struct list
{
    int data;
    struct list *next;
} node;


//��������
int Get_max(node *head);
int Num(node *head);
double Avg(node *head,int n);



// �����ʼ��
node *take()
{
    node *head =(node*)malloc(sizeof(node));

    int data;

    node *p;
    node *q;//ʼ��ָ��Ϊ��һ���ڵ�
    p=q=head;

    FILE * r= fopen("./data.txt","r");

    if(r==NULL)
    {
        cout << "An error occurred during the process of opening file!";
        return NULL;
    }

    while(fscanf(r,"%d",&data)!=EOF)
    {
        q= (node*)malloc(sizeof(node));
        q->data=data;
        p->next=q;
        p=q;
    }

    p->next=NULL;
    return head;

}
int Num(node *head)
{
    if(!head->next)
        return 1;
    else
        return Num(head->next)+1;
}

double Avg(node *head,int n)
{
    double a;
    if(!head->next)
        return head->data;
    else
    {
        a = Avg(head->next,n-1);
        return (a*(n-1)+head->data)/n;
    }

}

int Get_max(node *head)
{
    int m; // �洢���ֵ
    if(head->next == NULL)
    {
        return head->data;
    }

    else
        m = Get_max(head->next);

    return m>=head->data?m:head->data;

}


int main()
{
    node *head;
    head = take();


    int max = Get_max(head->next);
    cout << "The maximum integer is:" << max << endl;
    int num = Num(head->next);
    cout << "The number of nodes is:" << num << endl;

    int n = num;
    double avg = Avg(head->next,n);
    cout << "The average value is:" << avg << endl;
    return 0;


}
