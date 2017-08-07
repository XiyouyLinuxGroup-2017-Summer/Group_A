/*************************************************************************
	> File Name: thread.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年08月04日 星期五 15时38分43秒
    ************************************************************************/

/*  POSIX 下线程控制的实验程序残缺版 */ 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <ctype.h>
#include <pthread.h> 
#define MAX_THREAD 3 /* 线程的个数 */
unsigned long long main_counter, counter[MAX_THREAD]; 
/* unsigned long long是比long还长的整数 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* thread_worker(void*); 

int main(int argc,char* argv[])
{     
    int i, rtn, ch;     
    pthread_t pthread_id[MAX_THREAD] = {0}; /* 存放线程id*/ 
   
    int *param;
    for (i=0; i<MAX_THREAD; i++)
    {       
        /* 在这里填写代码，用pthread_create建一个普通的线程，
        线程id存入pthread_id[i]，线程执行函数是thread_worker
        并i作为参数传递给线程 */
        //申请内存临时保存参数
        param = (int*)malloc(sizeof(int));
        *param = i;
        pthread_create(&pthread_id[i],NULL,thread_worker,param);
    }    
    do
    {
        pthread_mutex_lock(&mutex);
        /* 用户按一次回车执行下面的循环体一次。按q退出 */          
        unsigned long long sum = 0;    
        /* 求所有线程的counter的和 */
        for (i=0; i<MAX_THREAD; i++) 
        {
            /* 求所有counter的和 */         
            sum += counter[i];             
            printf("%llu ", counter[i]);        
        }
        printf("%llu/%llu", main_counter, sum);
        pthread_mutex_unlock(&mutex);
    }while ((ch = getchar()) != 'q');
    pthread_mutex_destroy(&mutex);
    return 0;
} 
void* thread_worker(void* p)
{   
    int thread_num;  
    /* 在这里填写代码，把main中的i的值传递给thread_num */ 
    thread_num = *(int *)p;
    
    for(;;) 
    { /* 无限循环 */
     pthread_mutex_lock(&mutex);
     counter[thread_num]++; /* 本线程的counter加一 */ 
     main_counter++; /* 主counter 加一 */
     pthread_mutex_unlock(&mutex);
    } 
}


//进程资源共享

/*只是与我们平时写的单线程的程序不同的是，thread_worker 函数被调用了3次，
 * 而且3个函数在同时被执行。main_counter 和 counter[] 数组是全局的
 * ，所以3个子线程可以直接使用和改变它们。
 而thread_num 是函数内的局部变量，所以线程之间互相不可见。*/

