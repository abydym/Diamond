#include <stdio.h>
int num(int a1, int a2);
int main()
{
	int a1,a2,min_int;
	printf("Input First Number:");
	scanf("%d",&a1);
	printf("Input Second Number:");
	scanf("%d",&a2);
	num(a1,a2);
}
int num(int a1, int a2)
{
	int temp,i;
	if (a1>a2)
	{
		temp=a1;
		a1=a2;
		a2=temp;
	}
	for(i=a1;i<=a2;i++)
		printf("%5d",i);
		printf("\n");
	return 0;
}
