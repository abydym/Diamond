#define _XOPEN_SOURCE /* See feature_test_macros(7) */
#include<stdio.h>
#include<string.h>
#include<unistd.h>
char *crypt(const char *key, const char *salt);
int main()
{
	char passwd[13];
	char *key;
	char slat[2];
	key= getpass("Input First Password:");
	slat[0]=key[0];
	slat[1]=key[1];
	strcpy(passwd,crypt(key,slat));
	key=getpass("Input Second Password:");
	slat[0]=passwd[0];
	slat[1]=passwd[1];
	printf("After crypt(),1st passwd:%s\n",passwd);
	printf("After crypt(),2nd passwd:%s\n",crypt(key,slat));
}
