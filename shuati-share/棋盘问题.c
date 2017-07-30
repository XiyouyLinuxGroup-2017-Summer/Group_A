/*************************************************************************
	> File Name: 棋盘问题.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月26日 星期三 21时29分04秒
 ************************************************************************/
//解题关键DFS
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int n, k, ans;
char str[10][10];
int vis[100];

void dfs(int r, int k)
{
    if(k==0)
    {
        ans++;
        return;
    }

    for(int i=r; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(str[i][j]=='.' || vis[j]==1) continue;
            vis[j] = 1;
            dfs(i+1, k-1);
            vis[j] = 0;
        }
    }
}

int main(void)
{
    while(1)
    {
        scanf("%d %d", &n, &k);
        if(n==-1 && k==-1) break;
        memset(str, '\0', sizeof(str));
        memset(vis, 0, sizeof(vis));
        ans = 0;
        
        getchar();
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                str[i][j] = getchar();
            getchar();
        }

        dfs(0, k);
        printf("%d\n", ans);
    }
    return 0;
}
