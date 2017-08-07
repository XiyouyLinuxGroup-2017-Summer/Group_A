/*************************************************************************
	> File Name: thread.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年08月04日 星期五 14时34分14秒
 ************************************************************************/

/*  POSIX 下进程控制的实验程序残缺版 */ 
#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <signal.h>
#include <ctype.h> 
#include <stdlib.h>
#include <sys/wait.h>
/* 允许建立的子进程个数最大值 */
#define MAX_CHILD_NUMBER 10 
/* 子进程睡眠时间 */
#define SLEEP_INTERVAL 2 
int proc_number=0; 
/* 子进程的自编号，从0开始 */
void do_something(); 

int main(int argc, char* argv[])
{   
    /* 子进程个数 */
    int child_proc_number = MAX_CHILD_NUMBER; 
    int i, ch,status; 
    pid_t  child_pid; 
    pid_t pid[10]={0}; /* 存放每个子进程的id */ 
    if (argc > 1) /* 命令行参数第一个参数表示子进程个数*/ 
    {
        child_proc_number = atoi(argv[1]); 
        child_proc_number= (child_proc_number > 10) ? 10 :child_proc_number;
    } 
    for (i=0; i<child_proc_number; i++) { 
        /* 填写代码，建立child_proc_number个子进程要执行
        * proc_number = i; 
        * do_something(); 
        * 父进程把子进程的id保存到pid[i] */
        child_pid=fork();
            
        switch(child_pid)
        {
            case 0:
                proc_number = i;
                //printf("\n-------%d--------\n",proc_number);
                do_something();
                break;
            case -1:
                printf("process create fail\n");
                break;
            default:
                pid[i]=child_pid;
                break;
        }
    }
    /* 让用户选择杀死进程，数字表示杀死该进程，q退出 */
    while ((ch = getchar()) != 'q')  
    { 
        if (isdigit(ch)) 
        { 
            /*  填写代码，向pid[ch-'0']发信号SIGTERM， 
            * 杀死该子进程 */ 
            kill(pid[ch-'0'],SIGTERM);
            wait(&status);
        }
    } 
    /* 在这里填写代码，杀死本组的所有进程 */ 
    for(i=0;i<child_proc_number;i++)  
       kill(pid[i],SIGTERM); 
    return 0;
} 
void do_something() 
{ 
    for(;;) 
    {  
        printf("This is process No.%d and its pid is %d\n",proc_number,  getpid());
        sleep(SLEEP_INTERVAL); // 主动阻塞两秒钟
        printf("\n");
    }
}


/*
limeng    8650  0.0  0.0   4336   736 pts/0    S+   14:56   0:00 ./process 20
limeng    8651  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8652  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8653  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8654  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8655  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8656  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8657  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8658  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8659  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
limeng    8660  0.0  0.0   4336    76 pts/0    S+   14:56   0:00 ./process 20
*/
