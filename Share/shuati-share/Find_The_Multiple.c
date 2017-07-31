/*************************************************************************
    > File Name: Find The Multiple .c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月27日 星期四 20时53分29秒
 ************************************************************************/

//输入一个整数m，需要输出一个数，仅有1和0组成，并且能被n整除;

//DFS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int n,flag;

void dfs(long long m,int count)
{
    if(flag)
        return;//找到一个就不再找了，题意只要输出一个
    if(m%n==0)
    {
        flag=1;
        printf("%lld\n",m);
        return ;
    }
    if(count<19){    //n的范围为0-200,在long long 范围内一定可以找到
    dfs(m*10,count+1);
    dfs(m*10+1,count+1);
    }
}

int main(void)
{
    while(scanf("%d",&n)==1)
    {
        if(n==0)
            break;
        flag=0;
        dfs(1,1);//从数字1开始找，这时位数为1
    }
    return 0;
}
