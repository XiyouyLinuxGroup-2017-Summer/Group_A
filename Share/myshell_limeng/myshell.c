/*************************************************************************
	> File Name: myshell.c
	> Author:limeng 
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月27日 星期四 09时05分32秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<signal.h>
#include<setjmp.h>
#include <readline/readline.h>
#include <readline/history.h>

#define normal       0    //一般命令
#define out_redirect 1    //输出重定向
#define in_redirect  2    //输入重定向
#define have_pipe    3    //命令中有管道


void  print_prompt();
char* get_input(char *buf);
void explain_input(char * buf,int *argcount,char arglist[100][256]);
void do_cmd(int argcount,char arglist[100][256]);
int find_command(char *command);

void  print_prompt()
{
   // printf("\nInput exit  or  logout to quit\n");
}

char* get_input(char *buf)//获取输入的命令
{
    char dir[PATH_MAX];
    getcwd(dir,PATH_MAX);
    int l=strlen(dir);
    int i=l;
    if(l>1)
    {
        while(dir[i]!='/')
            i--;
        printf("\n[limeng@KID ");
        for(i=i+1;i<l;i++)
            printf("%c",dir[i]);
        printf("]");
    }
    else{   
        printf("\n[limeng@KID ");
        printf("%s]",dir);  
    }
    
    if(buf)
    {
        free(buf);
        buf=(char*)NULL;
    }
    buf = readline("--[myshell]$");
    int len=strlen(buf);
    if(len>256)
    {
        printf("Command is too long\n");
        exit(-1);
    }
    if(buf  && *buf)
        add_history(buf);
    return buf;

}


int main(int argc ,char **argv)
{

    int i;
    int argcount = 0;
    char arglist[100][256];
    char **arg;
    char *buf = NULL;
    
    signal(SIGINT,print_prompt); 

    while(1)
    {    
        buf = get_input(buf);

        //puts(buf);
        int l;
        l=strlen(buf);
        if(l==0)
            continue;
        buf[l]='\n';
        l++;
        buf[l]='\0';
        //若输入的命令为exit或者logout则退出本程序
        if(strcmp(buf,"exit\n") == 0 || strcmp(buf,"logout\n") == 0)
           break;
        for(i=0;i<100;i++)
           arglist[i][0]='\0';
        argcount=0;
        explain_input(buf , &argcount , arglist);
        do_cmd(argcount,arglist);
    }

    if(buf != NULL){
        free(buf);
        buf = NULL;
    }

    exit(0);
}

/*解析buf中的命令，将结果存入arglist中，命令以回车符'\n'结束*/
/*如果命令为ls -l /tmp,则arglist[0],arglist[1],arglist[2]分别为ls,-l和/tmp*/
void explain_input(char * buf,int *argcount,char arglist[100][256])
{
    char *p=buf;
    char *q=buf;
    int number = 0;
    int f=0;

    while(1)
    {
        if(p[0] == '\n')
            break;

        if(p[0] == ' ' )
            p++;
        else{
            q = p;
            number = 0;
            while(q[0]!=' '&&q[0]!='\n'){
                number++;
                q++;
            }
            if(strcmp(arglist[0],"ls")==0&&f==0)
            {
                f=1;
                strcpy(arglist[1],"--color=auto");//ls 输出上色
                arglist[1][12]='\0';
                *argcount=*argcount + 1;
            }
            strncpy(arglist[*argcount],p,number+1);
            arglist[*argcount][number] = '\0';
            //puts(arglist[*argcount]);
            *argcount=*argcount + 1;
            p=q;
        }
    }//用二维数组来保存各个参数
    if(*argcount==1 && strcmp(arglist[0],"ls")==0)
    {
        strcpy(arglist[1],"--color=auto");//只有单个ls，也要上色
        arglist[1][12]='\0';
        *argcount=*argcount + 1;
    }
}

void do_cmd(int argcount,char arglist[100][256])
{
    int flag=0;
    int how=0;
    int background=0;
    int status;
    int i;
    int fd;
    char * arg[argcount+2];
    char * argnext[argcount+1];
    char * file;
    pid_t pid;

    /*将命令取出*/
    for(i=0;i<argcount;i++)
    {        
        if(strncmp(arglist[i],"~",1)==0)
        {
            char * temp;
            temp = (char *)malloc(1000);
            strcpy(temp,arglist[i]);
            strcpy(arglist[i],"/home/limeng");
            arglist[i][12]='\0';
            strcat(arglist[i],temp+1);
            free(temp);
        }
        arg[i] = (char *)arglist[i];
    }
    arg[argcount] = NULL;

    //查看命令行是否有后台运行符
    for(i=0;i<argcount;i++)
    {
        if(strncmp(arg[i],"&",1)==0)
        {
            if(i == argcount -1)
            {
                background = 1;
                arg[argcount-1]=NULL;
                break;
            }
            else{
                printf("Wrong Command\n");
                return ;
            }
        }
    }
    //cd
    if(strcmp(arg[0],"cd")==0)
    {
        if(argcount==1)
        { 
            strcpy(arglist[1],"/home/limeng");
            arg[1]=(char *)(arglist[1]);
            //arglist[2][0]='\0';
            arg[2]=NULL;
        }    
        if(chdir(arg[1])==-1)
            printf("chdir error\n");
        return ;
    }
    
    int flag2=0;   
    //命令中含有多个>,<,|符号，本程序不支持，或者输入格式不对，本程序也不支持
    for(i=0; arg[i]!=NULL; i++){
        if(strcmp(arg[i],">") == 0 || strcmp(arg[i],">>")==0)
        {
            if(strcmp(arg[i],">>")==0)
                flag2=1;
            flag++;
            how = out_redirect;
            if (arg[i+1] == NULL)
                flag++;
        }//>不能出现在结尾
        if(strcmp(arg[i],"<") == 0)
        {
            flag++;
            how = in_redirect;
            if (i==0)
               i++;
        }//<不能出现在开头
        if(strcmp(arg[i],"|") == 0)
        {
            flag++;
            how = have_pipe;
            if(arg[i+1] == NULL)
                flag++;
            if(i == 0)
                flag++;
        }//管道只能在中间出现
    }
    if(flag > 1)
    {
        printf("Wrong Command");
        return ;
    }

    if(how == out_redirect)//命令中只有一个输出重定向>
    {
        for(i=0; arg[i]!=NULL; i++)
        {
            if(strcmp(arg[i],">")==0||strcmp(arg[i],">>")==0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
            
        }
    }
    
    if(how == in_redirect)//命令中只有一个输入重定向<
    {                                                   
        for(i=0; arg[i]!=NULL; i++)                    
        {                                              
            if(strcmp(arg[i],"<")==0)                  
            {                                          
                 file = arg[i+1];                       
                 arg[i] = NULL;                         
            }                                                                               
        }                                              
    }
    
    //命令中只有一个管道
    if(how == have_pipe)
    {   
        //把管道的后门的部分存入argnext中，中道后面的部分是一个可执行的shell命令
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],"|")==0)
            {
                arg[i] = NULL;
                int j;
                for (j=i+1;arg[j]!=NULL;j++)
                {
                    argnext[j-i-1] = arg[j];
                }
                argnext[j-i-1] = arg[j];
                break;
            }
        }       
    }
    if((pid = fork())<0)
    {
        printf("fork error\n");
        return ;
    }

    switch(how)
    {
        case 0:
            /*pid 为0说明是子进程，在子进程中执行输入的命令*/
            /*输入的命令中不含>,<和|*/
            if(pid == 0){
                if(!(find_command(arg[0]))){
                    printf("%s :command not found\n",arg[0]);
                    exit(0);
                }
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 1:
            /*输入的命令中有输出重定向符>,>>*/
            if(pid==0)
            {
                if(!(find_command(arg[0]))){
                    printf("%s :command not found\n",arg[0]);
                    exit(0);
                }
                if(flag2) 
                    fd = open(file,O_RDWR|O_CREAT|O_APPEND,0644);
                else    
                    fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
                dup2(fd,1); //0 标准输入， 1 标准输出，2 标准错误
                //新打开的文件描述符号，代替了1这个描述符
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 2:
            /*输入的命令中有输入重定向符<*/
            //是从文件中取出数据到指定的文件中
            if(pid==0)
            {
                if(!(find_command(arg[0]))){
                    printf("%s :command not found\n",arg[0]);
                    exit(0);
                }
                fd = open(file,O_RDONLY);
                dup2(fd,0);//新打开的文件描述符号代替了标准输入   
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 3:
             /*输入的命令中有管道符号|*/
            if(pid==0)
            {
                int pid2;
                int status;
                int fd2;

                if((pid2 = fork())<0){
                    printf("fork2 error\n");
                    return ;
                    }
                else if(pid2 ==0 ){ 
                    if(!(find_command(arg[0]))){
                        printf("%s : command not found\n",arg[0]);
                        exit(0);
                    }
                fd2 = open("/tmp/youdonotknowfile",O_WRONLY|O_CREAT|O_TRUNC,0644);
                dup2(fd2,1);
                execvp(arg[0],arg);
                exit(0);
                }

                if(waitpid(pid2,&status,0) == -1)
                    printf("wait for child process error");

                if(!find_command(argnext[0])){
                    printf("%s : command not found\n",argnext[0]);
                    exit(0);
                }

                fd2 = open("/tmp/youdonotknowfile",O_RDONLY);
                dup2(fd2,0);
                execvp(argnext[0],argnext);

                if(remove("/tmp/youdonotknowfile"))
                    printf("remove error\n");
                exit(0);
            }
            break;
        default:
            break;
    }

    /*若命令中有&,表示后台运行，父进程直接返回，不等待子进程结束*/
    if(background == 1)
    {
        printf("[process id：%d]\nfinished\n",pid);
        usleep(50000);
        return ;
    }

    /*父进程等待子进程结束*/
    if(waitpid(pid,&status,0)==-1)
        printf("wait for child process error\n");
    return ;
}

/*查找命令中的可执行程序*/
int find_command(char *command)
{
    DIR * dp;
    struct dirent * dirp;
    char * path[]={"./","/bin","/usr/bin/",NULL};

    /*使当前目录下的程序可以运行，去掉'./'*/
    if(strncmp(command,"./",2) == 0)
    {
        command = command + 2;
    }

    /*分别在当前目录、/bin和/usr/bin目录查找可执行的程序*/
    int i=0;
    while(path[i] != NULL)
    {
        if((dp=opendir(path[i])) == NULL)
            printf("can't open /bin \n");
        while((dirp = readdir(dp))  != NULL){
            if(strcmp(dirp->d_name,command) == 0)
            {
                closedir(dp);
                return 1;
            }    
        }
        closedir(dp);
        i++;
    }
    return 0;
}
