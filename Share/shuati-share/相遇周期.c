/*相遇周期问题

输入：输入数据的第一行为一个正整数T, 表示测试数据的组数然后是T组测试数据. 每组测试数据包含两组正整数，用空格隔开。每组包含两个正整数，表示转n圈需要的天数(26501/6335，表示转26501圈要6335天)，用'/'隔开。 

输出：对于每组测试数据，输出它们的相遇周期，如果相遇周期是整数则用整数表示，否则用最简分数表示。 
*/

/*解决思路：两个卫星的周期T不同，一定会相遇。转一圈所用的时间分别为n/a和m/b;相当于求两者的最小公倍数
 * 要注意是否是整数周期，分数化简可以将分子和分母同时除以它们的最大公约数。*/

#include<stdio.h>

int gcd(long long a,long long b)
{
    return b==0?a:gcd(b,a%b);
}
//求最大公约数 
int main(void)
{
	int T;
	long long a,b,n,m,lcm;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld/%lld %lld/%lld",&n,&a,&m,&b);
        lcm=(n*a*b*m)/gcd(n*b,m*a);//通分过后的分母的最小公倍数 
        if(lcm%(a*b)==0)           //是整周期就输出
            printf("%lld\n",lcm/(a*b));
        else                       //不是整数用最简分数表示
            printf("%lld/%lld\n",lcm/gcd(lcm,a*b),(a*b)/gcd(lcm,a*b));//化简
	}
	return 0;
}
