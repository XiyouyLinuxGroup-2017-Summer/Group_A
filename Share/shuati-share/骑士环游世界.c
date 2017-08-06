/*************************************************************************
	> File Name: A-Knight's-Journey.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月31日 星期一 19时03分43秒
 ************************************************************************/
//A Knight's Journey 
//问题：整天待在方块里的骑士感到特别的无聊，于是他决定来一场说走就走的旅行。
//然而他只能走日字，如右图所示，如果骑士当前在棋盘的正中央，他可以走标记有白点的八个区域。
//骑士知道世界是一个列数和行数均不超过8（即8×8）的棋盘。
//并且骑士有一点强迫症，如果用A-Z来表示列，1-99来表示横行，他只愿意走字典序最小的一条道路。
//你能帮助勇敢的骑士制定一个适合他的旅行计划，使得他可以走遍整个棋盘吗？骑士可以在任一方块出发或者结束。


//输入：第一行中有一个正整数n，代表数据有n组。
//对于每组数据，都含有两个正整数p和q(1 <= p * q <= 26)，代表棋盘有p行q列。


//输出：每组数据首先应当输出"Scenario #i:"，i代表输出的是第i组数据的结果。
//然后在一行之内输出一条可以走遍棋盘的路径，如果有多条路径可以走遍棋盘，那么输出按字典序排序第一的路径。
//最后，留一个空行。若现在是最后一条数据，则不留空行。

//在输出路径时，用A代表第一列，B代表第二列..以此类推。而使用1代表第一行，2代表第二行。
//例如，若要表示从第一行第一列到第二行第三列，可以用字符串：A1C3来表示。


//解题思路：假设可以从中间的点，走完所有的格子，那么一定经过第一个格子，
//所以从（1,1）开始走一定也可以遍历完所有的点，此时的字典顺序一定为最小
//即若有一条路径，则字典顺序最小的从A1开始
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1};  
int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2};//分别表示8个方向  

int vis[9][9];
int p,q;
int flag;

struct Step{
    char x, y;
} path[27];//来存储结果

int check(int x,int y)//判断在范围内且没有被访问过，而且是第一次找到路径
{
    if(vis[x][y]==0&&x>0&&y>0&&x<=p&&y<=q&&!flag)
        return 1;
    return 0;
}

void dfs(int x,int y,int step)
{
    path[step].y = y + 'A' - 1;   //将 int 转为 char
    path[step].x = x + '0';
    if(step==p*q)//走完所有的格子，就返回
    {
        flag=1;
        return ;
    }
    int xx,yy,t;
    for(t=0;t<8;t++)
    {
        xx=x+dx[t];
        yy=y+dy[t];
        if(check(xx,yy))
        {
            vis[xx][yy]=1;//标记
            dfs(xx,yy,step+1);//递归
            vis[xx][yy]=0;//恢复标记
        }
    }
}

int main(void)
{
    int n,i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        flag=0;
        memset(vis,0,sizeof(vis));
        scanf("%d %d",&p,&q);
        vis[1][1]=1;
        dfs(1,1,1);//从（1,1）开始走
        printf("Scenario #%d:\n",i); 
        if(flag){
            for(j=1;j<=p*q;j++)
                printf("%c%c",path[j].y,path[j].x);
            printf("\n");   
        }
        else
            printf("impossible\n");
        if(i!=n)
            printf("\n");//控制格式
    }
    return 0;
}
