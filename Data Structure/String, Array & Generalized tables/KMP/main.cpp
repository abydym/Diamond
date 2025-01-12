#include <iostream>
using namespace std;
#define MAXLEN 255
typedef struct
{
    char ch[MAXLEN+1];
    int length;
}SString;

//next
void get_next(SString T,int next[]);
//nextval
void get_nextval(SString T,int nextval[]);


int main()
{
    SString T;
    cout << "Please input T:";
    for(int i=1; i<8;i++)
        cin >> T.ch[i];
    T.length = 8;
    int next[8];
    int nextval[8];
    get_next(T,next);
    get_nextval(T,nextval);
    cout << "next:" ;
    for(int i=1;i<8;i++)
        cout << next[i] << " ";
    cout << endl;
    cout << "nextval:";
    for(int i=1;i<8;i++)
        cout << nextval[i] << " ";

    return 0;
}
void get_next(SString T,int next[])
{
    int i=1,j=0;
    next[1] = 0;
    while(i<T.length)
    {
        if(j==0 || T.ch[j]==T.ch[i])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}
void get_nextval(SString T,int nextval[])
{
    int i=1,j=0;
    nextval[1] = 0;
    while(i<T.length)
    {
        if(j==0 || T.ch[j]==T.ch[i])
        {
            ++i;
            ++j;
            if(T.ch[i] != T.ch[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j];
    }
}

