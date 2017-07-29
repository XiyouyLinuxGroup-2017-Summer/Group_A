/*************************************************************************
	> File Name: 全排列.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月28日 星期五 08时15分08秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

//全排列问题

int n;
char  a[15];
char re[15];
int vis[15];
//假设有n个字符要排列，把他们依次放到n个箱子中
//先要检查箱子是否为空，手中还有什么字符，把他们放进并标记。
//放完一次要恢复初始状态，当到n+1个箱子时，一次排列已经结束
void dfs(int step)
{
    int i;
    if(step==n+1)
    {
        for(i=1;i<=n;i++)
            printf("%c",re[i]);
        printf("\n");
        return ;//排列结束要输出
    }
    for(i=1;i<=n;i++)
    {
        if(vis[i]==0)
        {
            re[step]=a[i];
            vis[i]=1;
            dfs(step+1);
            vis[i]=0;
        }
    }
    return ;
}

int main(void)
{
    int T;
    scanf("%d",&T);
    getchar();
    while(T--)
    {
        memset(a,0,sizeof(a));
        memset(vis,0,sizeof(vis));
        scanf("%s",a+1);
        n=strlen(a+1);
        dfs(1);//从第一个箱子开始
    }
    return 0;
}
