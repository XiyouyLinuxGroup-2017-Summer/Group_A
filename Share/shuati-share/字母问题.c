/*************************************************************************
	> File Name: B.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年08月02日 星期三 09时21分16秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

/*问题：
有一个单人的字母游戏，在一个R行C列的矩阵上进行。矩阵上的每一个点都写着一个大写字母。
在游戏开始之前，有一个指示物处于矩阵的左上角（第1行第1列），玩家可以向上下左右四个方向
移动这个指示物，但是每个字母只可以经过一次（包括刚开始指向的字母）。这个游戏的目标就是
尽可能经过更多的字母。现在请你写一个程序，求出在给定矩阵情况下，最多可以经过多少个不同的字母？

输入：
输入包含多组数据。
每组数据的第一行包含两个整数R和C，代表是一个R行C列的矩阵（ 1 <= R, S <= 20）。
接下来的R行每行包含S个字母，每一行代表矩阵中该行的字母情况。

输出：
对于每一组数据，你只需要在一行中输出一个数字n，代表指示物最多可以经过多少个不同的字母。


*/

int r, c, result;  
const int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};//四个方向  
int visletter[26], vis[21][21];//分别记录字母和位置坐标  
char data[21][21];  
  
int  Judge(int i, int j)  
{  
    if(!visletter[data[i][j] - 'A'] && !vis[i][j] && i >= 0 && i < r && j >= 0 && j < c)
        return 1;//这个字母没有被记录，该点没有被访问过，且在范围内
    return 0;
}  
  
void dfs(int i, int j, int step)  
{  
    visletter[data[i][j] - 'A'] = vis[i][j] = 1;//标记  
    for(int k = 0; k < 4; k++)  
    {  
        int ii = i + dir[k][0];  
        int jj = j + dir[k][1];  
        if(Judge(ii, jj))  
        {  
            dfs(ii, jj, step + 1);  //进入下一层搜索
            visletter[data[ii][jj] - 'A'] = vis[ii][jj] = 0;//恢复标记  
        }  
    }  
    if(result < step) 
        result = step;  //记录最大
}  
  
int main(void)  
{  
    while(scanf("%d %d", &r, &c) != EOF)  
    {  
        result = 0;  
        for(int i = 0; i < r; i++)  
            scanf("%s", data[i]);  
        memset(visletter, 0, sizeof(visletter));  
        memset(vis, 0, sizeof(vis));  
        dfs(0, 0, 1);  //从（0,0）开始搜索
        printf("%d\n", result);  
    }  
}  
