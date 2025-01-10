#include <iostream>
using namespace std;
#define MAX 32767
#define VER 100

typedef struct
{
    int dist;
    int know;
    int path;
    string name;
}Vertex;

int graph[VER][VER];

void initGraph(int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                graph[i][j]=0;
            }
            else
            {
                graph[i][j]=MAX;
            }
        }
    }
}

void addedge(int u,int v,int w)
{
    graph[u][v]=w;
    graph[v][u]=w;
}

void dijkstra(Vertex *ver,int n,int start)
{
    for(int i=0;i<n;i++)
    {
        ver[i].dist=MAX;
        ver[i].know=0;
        ver[i].path=-1;
    }
    ver[0].name="����";
    ver[1].name="�ݷ�ͼ���";
    ver[2].name="����¥";
    ver[3].name="����¥";
    ver[4].name="�Ķ�¥";
    ver[5].name="����¥";
    ver[6].name="������¥";

    ver[start].dist=0;

    while(1)
    {
        int u=-1;
        int minDist=MAX;

        for(int i=0;i<n;i++)
        {
            if(!ver[i].know && ver[i].dist<minDist)
            {
                minDist=ver[i].dist;
                u=i;
            }
        }
        if(u==-1)
        {
            break;
        }
        ver[u].know=1;

        for(int v=0;v<n;v++)
        {
            if(graph[u][v]!=MAX && !ver[v].know)
            {
                int newDist = ver[u].dist + graph[u][v];
                if(newDist<ver[v].dist)
                {
                    ver[v].dist=newDist;
                    ver[v].path=u;
                }
            }
        }
    }
}

void ptSP(Vertex *ver,int n,int start)
{
    for (int i = 0; i < n; i++) {
        if (i == start) {
            continue;
        }
        cout<<"��"<<ver[start].name<<"��"<<ver[i].name<<"�ľ���Ϊ";
        if (ver[i].dist == INT_MAX) {
            printf("��Ǹ���˴����ɴ�\n");
        } else {
            cout<<ver[i].dist<<endl;
            int path = i;
            while (path != -1) {
                cout<<ver[path].name<<"<-";
                path = ver[path].path;
            }
            cout<<"\b\b\n";
        }
    }
}
void welcome()
{
    cout<<"------------"<<"���մ�ѧ����У������·����ѯϵͳ"<<"------------"<<endl;
    cout<<"�۾����贺��Ӱ����֦ͩ�¶�ؾ����ʽ�伮���ϳ��������������º���"<<endl;
    cout<<"���մ�ѧ����У����7���ص㣬�ֱ��ǣ�"<<endl;
    cout<<"(0)����\t\t(1)�ݷ�ͼ���\t\t(2)����¥\t(3)����¥"<<endl;
    cout<<"(4)�Ķ�¥\t(5)����¥\t\t(6)������¥"<<endl;
}
void func()
{
    cout<<endl<<"��ϵͳ�ɼ���Ĺ������£�"<<endl;
    cout<<"(A)�㵽���������·��\t\t(B)ĳ����������о�������·��"<<endl;
    cout<<"(C)�˳�"<<endl;
    cout<<"����������Ҫ�Ĺ��ܣ�";
}

void PtoP(Vertex *ver,int start,int end)
{
    cout<<"��"<<ver[start].name<<"��"<<ver[end].name<<"�ľ���Ϊ��";
        if (ver[end].dist == INT_MAX) {
            printf("��Ǹ���˴����ɴ�\n");
        }
        else {
            cout<<ver[end].dist<<endl;
            int path = end;
            while (path != -1) {
                cout<<ver[path].name<<"<-";
                path = ver[path].path;
            }
            cout<<"\b\b\n";
        }
}

int main()
{
    int n=7;
    initGraph(7);

    addedge(0,1,2);
    addedge(0,2,5);
    addedge(1,3,6);
    addedge(2,3,1);
    addedge(3,4,1);
    addedge(3,5,2);
    addedge(4,6,7);
    addedge(5,6,3);

    Vertex ver[n];

    welcome();
    int exit=1;
    char choose;
    while(exit)
    {
        func();
        cin>>choose;
        switch (choose)
        {
        case 'A':
            int startVer,end;
            cout<<"��ֱ����������յ����ţ��ÿո����";
            cin>>startVer>>end;
            dijkstra(ver,n,startVer);
            PtoP(ver,startVer,end);
            choose = NULL;
            break;
        case 'B':
            cout<<"������������Ų����»س���";
            cin>>startVer;
            dijkstra(ver,n,startVer);
            ptSP(ver,n,startVer);
            choose = NULL;
            break;
        case 'C':
            cout<<"�ټ�����ӭ�´�������"<<endl;
            exit=0;
        }
    }
    return 0;
}