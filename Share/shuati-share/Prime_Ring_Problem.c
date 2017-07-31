/*问题：
一个环由个圈组成，把自然数1，2，...N分别放在每一个圆内，
数字的在两个相邻圈之和应该是一个素数。
注意：第一圈数应始终为1。

input: N(0~20)

output:输出格式如下所示的样品。每一行表示在环中的一系列圆号码从1开始顺时针和按逆时针方向。编号的顺序必须满足上述要求。打印解决方案的字典顺序。 
*/

//Prime Ring Problem
//全排列问题其实思路差不多，只是需要判断的条件比较多
//化大为小

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int book[25];
int result[25];
int n;
int num;
//判断是否为素数
int prime(int n)
{
    if(n<=1)
        return 0;
    int i;
    for(i=2;i*i<=n;i++)
    {
        if(n%i==0)
            break;
    }
    if(i*i>n)
        return 1;
    return 0;
}
//判断是否能将当前的数字放到当前的圈内
int check(int i,int step)
{
    if((book[i]==0) && prime(i+result[step-1])==1)
    {
        if(step==n-1)
        {
            if(!prime(i+result[0]))
                return 0;
        }
        return 1;
    }
    return 0;
}

void dfs(int step)
{
    if(step==n)//判断边界
    {
        int a;
        printf("%d",result[0]);
        for(a=1;a<n;a++)
        {
            printf(" %d",result[a]);
        }
        printf("\n");
        return ;
    }
    int i;
    for(i=2;i<=n;i++)//遍历每一种情况
    {
        if(check(i,step))//check是否满足
        {
            book[i]=1;//标记
            result[step]=i;//记录结果
            dfs(step+1);//继续往下搜索
            book[i]=0;//恢复初始状态
        }
    }
}

int main(void)
{

    while(scanf("%d",&n)!=EOF)
    {
        num++;
        memset(result,0,sizeof(result));
        memset(book,0,sizeof(book));
        result[0]=1;
        printf("Case %d:\n",num);//格式比较容易出错
        dfs(1);
        printf("\n");
    }
    return 0;
}
