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
    ver[0].name="南门";
    ver[1].name="逸夫图书馆";
    ver[2].name="生化楼";
    ver[3].name="主教楼";
    ver[4].name="文东楼";
    ver[5].name="文西楼";
    ver[6].name="互联大楼";

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
        cout<<"从"<<ver[start].name<<"到"<<ver[i].name<<"的距离为";
        if (ver[i].dist == INT_MAX) {
            printf("抱歉，此处不可达\n");
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
    cout<<"------------"<<"安徽大学龙河校区游览路线咨询系统"<<"------------"<<endl;
    cout<<"眼镜湖描春晖影，梧桐枝下鹅池静；问津典籍古韵长，龙河有你启新航。"<<endl;
    cout<<"安徽大学龙河校区有7个地点，分别是："<<endl;
    cout<<"(0)南门\t\t(1)逸夫图书馆\t\t(2)生化楼\t(3)主教楼"<<endl;
    cout<<"(4)文东楼\t(5)文西楼\t\t(6)互联大楼"<<endl;
}
void func()
{
    cout<<endl<<"本系统可计算的功能如下："<<endl;
    cout<<"(A)点到点距离和最短路线\t\t(B)某点出发的所有距离和最短路线"<<endl;
    cout<<"(C)退出"<<endl;
    cout<<"请输入你需要的功能：";
}

void PtoP(Vertex *ver,int start,int end)
{
    cout<<"从"<<ver[start].name<<"到"<<ver[end].name<<"的距离为：";
        if (ver[end].dist == INT_MAX) {
            printf("抱歉，此处不可达\n");
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
            cout<<"请分别输入起点和终点的序号，用空格隔开";
            cin>>startVer>>end;
            dijkstra(ver,n,startVer);
            PtoP(ver,startVer,end);
            choose = NULL;
            break;
        case 'B':
            cout<<"请输入起点的序号并按下回车键";
            cin>>startVer;
            dijkstra(ver,n,startVer);
            ptSP(ver,n,startVer);
            choose = NULL;
            break;
        case 'C':
            cout<<"再见，欢迎下次再来！"<<endl;
            exit=0;
        }
    }
    return 0;
}