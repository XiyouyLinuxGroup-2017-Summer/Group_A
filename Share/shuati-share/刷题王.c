/*************************************************************************
	> File Name: A.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年08月01日 星期二 08时10分14秒
 ************************************************************************/
/*已知：
 * ①zty是一个很强大的人，他解决第1个问题所需时间仅仅为0分钟。
 * ②一个题花费的时间越多，那么它肯定更难。
 * ③而正如前面所说的，zty总是选择难度不小于上一题的题目来解决。

输入：输入包含多组测试数据。每组输入数据的最开始是一个整数n，
代表有n个难题。( 2< n < 15)。接下来的n行每行包含n个整数，假设我们用T(i,j)
表示第i行第j列的整数的话，T(i,j)的意思是当zty解决了问题i之后，解决问题j需要
花费T(i,j)分钟。我们保证：0 <= n <= 10.

输出：对于每组输入数据，输出他最多可以刷多少道题。
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int n,result;
int i,j;
int retime[101][101];//用来存刷完i题再刷j题所用时间
int vis[101]; //存该题是否刷过

void dfs(int i,int time,int step)
{
    int j;
    if(result<step)
        result = step;   //记录结果
    for(j=1;j<n;j++)
    {
        if(vis[j]==0&&retime[i][j]>=time)//判断是否已经刷过该题，后来的难度是否更大
        {
            vis[j]=1;
            dfs(j,retime[i][j],step+1);
            vis[j]=0;
        }
    }
}

int main(void)
{
    while(scanf("%d",&n)!=EOF)
    {
        result=0;
        memset(vis,0,sizeof(vis));
        memset(retime,0,sizeof(retime));
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&retime[i][j]);
        dfs(0,0,1);//从第0道题开始，此时刷完一题
        printf("%d\n",result);
    }
    return 0;
}
