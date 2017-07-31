/*************************************************************************
	> File Name: B.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月25日 星期二 08时23分05秒
 ************************************************************************/
//A + B Problem II 
//大整数相加问题，数字的长度不超过1000位
//解决思路：首先数据特别大，long long也存不下，只能用字符串来操作
//问题的关键在于要将两个要相加的数，按位对齐存好，不够前面要补零，
//并且要保证最高位多一个，可能来存进位的数。
//从最小位依次相加，考虑是否进位，最后要按格式输出，注意空格。

//与这题类似的，可以思考大整数相减问题；也可以去思考如果不是整数该怎么处理

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
    char a[1005];
    char b[1005];
    int n,l1,l2,i,max,count=1;
    scanf("%d",&n);
    getchar();
    while(n--)
    {
        scanf("%s%s",a,b);
        l1=strlen(a);
        l2=strlen(b);
        char d[1005];
        char c[1005];
        memset(c,'0',1005);
        memset(d,'0',1005);
        if(l1>l2)
            max=l1;
        else 
            max=l2;
        c[max+1]='\0';
        d[max+1]='\0';
        //按位对齐存好
        for(i=max;l1>0;i--,l1--)
             c[i]=a[l1-1];
        for(i=max;l2>0;i--,l2--)
             d[i]=b[l2-1];
        for(i=max;i>=0;i--)
        {
            int temp=c[i]+d[i]-'0'-'0';
            if(temp>=10)   //判断是否进位
            {
                c[i-1]=c[i-1]+1;
                d[i]=c[i]+d[i]-'0'-10;
            }else
                d[i]=c[i]+d[i]-'0';
        }
        if(count-1!=0)//按格式输出两组结果间有分隔
            printf("\n");
        if(d[0]=='0')
            printf("Case %d:\n%s + %s = %s\n",count,a,b,d+1);
        else
            printf("Case %d:\n%s + %s = %s\n",count,a,b,d);//C大写，+和=的两侧都有空格
        count++;
    }
    return 0;
}
