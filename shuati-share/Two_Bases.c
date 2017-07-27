/*************************************************************************
	> File Name: Two Bases .c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月27日 星期四 19时10分24秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

/*pow函数的参数最好要用double类型*/
int main(void)
{
    double n,x,m,y;
    double sum1=0,sum2=0;
    double temp;
    scanf("%lf%lf",&n,&x);
    while(n--)
    {
        scanf("%lf",&temp);
        sum1=sum1+temp*pow(x,n);
    }

    scanf("%lf%lf",&m,&y);
    while(m--)
    {
        scanf("%lf",&temp);
        sum2=sum2+temp*pow(y,m);
    }

    if(sum1<sum2)
        printf("<");
    else if(sum1==sum2)
        printf("=");
    else 
        printf(">");
    putchar('\n');
    return 0;
}
