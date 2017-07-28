/*************************************************************************
	> File Name: B.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月28日 星期五 15时56分46秒
 ************************************************************************/
//A - Oil Deposits 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char a[105][105];
int n,m,result;
int dir[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};

int check(int x,int y)//检查是否有石油
{
    if(x>=0&&x<m&&y>=0&&y<n&&a[x][y]=='@')
        return 1;
    return 0;
}

int dfs(int x, int y)
{
    int i,xx,yy;
    if(check(x,y))
    {
        a[x][y]='.'; //统计之后就可以把该油田标记，且不用恢复（要不会重复），
                    //也可以用一个数组来存每个点的访问情况，但是感觉没必要，浪费空间
        for(i=0;i<8;i++)
        {
            xx=x+dir[i][0];
            yy=y+dir[i][1];
            dfs(xx,yy);//依次检查8个方向
        }
        return 1;
    }
    return 0;
}


int main(void)
{
    int i,j;

    while(scanf("%d %d",&m,&n)==2)
    {
        if(m==0&&n==0)
            break;
        result = 0;
        memset(a,0,sizeof(a));
        for(i=0;i<m;i++)
            scanf("%s",a[i]);
    
        for(i=0;i<m;i++)//在每一个点都搜索一次
        {
            for(j=0;j<n;j++)
            {
                if(dfs(i,j))//找到油田就可以将结果加一
                    result++;
            }
        }
        printf("%d\n",result);
    }

    return 0;
}
