/*************************************************************************
	> File Name: my_ls.c
	> Author: limeng
	> Mail: ldx19980108@gmail.com
	> Created Time: 2017年07月20日 星期四 10时24分15秒
 ************************************************************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>


#define PARAM_NONE 0    //无参数
#define PARAM_A 1       //-a:显示所有文件
#define PARAM_L 2      //-l:一行只显示一个文件的详细信息
#define PARAM_R 4
#define MAXROWLEN 90  //一行显示的最多的字符数

char a[12];
int g_leave_len = MAXROWLEN;      //一行剩余长度，用于输出对齐
int g_maxlen;                     //存放某目录下最长文件名的长度

/*错误处理函数，打印出错误所在行数和错误信息*/
void my_err(const char *err_string,int line){
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

void get_quanxian(struct stat buf){
    
    if(S_ISLNK(buf.st_mode)){
        a[0]='l';
    }else if(S_ISREG(buf.st_mode)){
        a[0]='-';
    }else if(S_ISDIR(buf.st_mode)){
        a[0]='d';
    }else if(S_ISCHR(buf.st_mode)){
        a[0]='c';
    }else if(S_ISBLK(buf.st_mode)){
        a[0]='b';
    }else if(S_ISFIFO(buf.st_mode)){
        a[0]='f';
    }else if(S_ISSOCK(buf.st_mode)){
        a[0]='s';
    }

    /*获取并打印文件所有者的权限*/
    if(buf.st_mode & S_IRUSR){
        a[1]='r';
    }else{
        a[1]='-';
    }
    if(buf.st_mode & S_IWUSR){
        a[2]='w';
    }else{
        a[2]='-';
    }
    if(buf.st_mode & S_IXUSR){
        a[3]='x';
    }else{
        a[3]='-';
    }


    /*获取并打印与文件所有者同组的用户对文件的操作*/
    if(buf.st_mode & S_IRGRP){
        a[4]='r';
    }else{
        a[4]='-';
    }
    if(buf.st_mode & S_IWGRP){
        a[5]='w';
    }else{
        a[5]='-';
    }
    if(buf.st_mode & S_IXGRP){
        a[6]='x';
    }else{
        a[6]='-';
    }
    
    /*获取并打印与文件所有者同组的用户对文件的操作*/
    if(buf.st_mode & S_IROTH){
        a[7]='r';
    }else{
        a[7]='-';
    }
    if(buf.st_mode & S_IWOTH){
        a[8]='w';
    }else{
        a[8]='-';
    }
    if(buf.st_mode & S_IXOTH){
        a[9]='x'; 
    }else{
        a[9]='-';
    }
}
/*
蓝色表示目录；
绿色表示可执行文件；
红色表示压缩文件；××
浅蓝色表示链接文件；
灰色表示其它文件；
红色闪烁表示链接的文件有问题了；××
黄色是设备文件，包括block, char, fifo。
*/
void print_name(char * str)
{

    if(a[0]=='d')
        printf("\033[34m%-s\033[0m",str);
    else if(a[0]=='l')
        printf("\033[1;34m%-s\033[0m",str);
    else if(a[0]=='f'||a[0]=='b'||a[0]=='c')
        printf("\033[33m%-s\033[0m",str);
    else if(a[3]=='x')
        printf("\033[32m%-s\033[0m",str);
    else    
    printf("%-s",str);
        
}

/*获取文件的属性并打印*/
void display_attribute(struct stat buf,char *name)
{
    char buf_time[32];
    struct passwd *psd;   //从该结构体中获取文件所有者的用户名
    struct group *grp;    //从该结构体中获取文件所有者所属组的组名
    
    get_quanxian(buf);
    
    printf("%s  ",a);

    /*根据uid和gid获取文件所有者的用户名与组名*/
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%4d ",buf.st_nlink);
    printf("%-8s",psd->pw_name);
    printf("%-8s",grp->gr_name);

    printf("%6d",buf.st_size);
    strcpy(buf_time,ctime(&buf.st_mtime));
    buf_time[strlen(buf_time)-1]='\0';   //去掉换行符
    printf(" %s  ",buf_time);
    print_name(name);
    printf("\n");
}

void display_single(struct stat buf,char *name)
{
    int i,len;

    //本行不能再打印出一个文件名
    if(g_leave_len<g_maxlen)
    {
        printf("\n");
        g_leave_len=MAXROWLEN;
    }

    get_quanxian(buf);


    len = strlen(name);
    len = g_maxlen-len;
    
    print_name(name);
    
    for(i=0;i<len;i++)
    {
        printf(" ");
    }
    printf("  ");      //输出2个空格
    g_leave_len=g_leave_len-(g_maxlen)-2;
}

/*
 * 根据命令行参数和完整路径名显示目标文件
 * 参数flag:命令行参数
 * 参数pathname:包含了文件名的路径名
 */

void display(int flag,char *pathname)
{
    int i,j;
    struct stat buf;
    char name[NAME_MAX+1];

    /*从路径中解析出文件名,把所有的父目录都去除掉*/
    for(i=0,j=0;i<strlen(pathname);i++){
        if(pathname[i] == '/'){
            j=0;
            continue;
        }
        name[j++]=pathname[i];
    }
    name[j]= '\0';

    if(lstat(pathname,&buf)==-1)
    {
        if(errno==13)
        {
            printf("权限不足\n");
            return ;
        }
        my_err("stat",__LINE__);
    }

    switch(flag)
    {
        case PARAM_NONE:    //没有任何参数
        case PARAM_R:
            if(name[0]!='.'){
                display_single(buf,name);
            }
        break;
        case PARAM_A:       //-a
        case PARAM_A+PARAM_R:
            display_single(buf,name);
            break;
        case PARAM_L:
        case PARAM_R+PARAM_L:
            if(name[0]!='.'){   //-l
                display_attribute(buf,name);
            }
            break;      
        case PARAM_A+PARAM_L: 
        case PARAM_A+PARAM_L+PARAM_R:
            display_attribute(buf,name);
            break; 
        default:
            break;

    }
}

void display_dir(int flag_param,char *path)
{
    
    DIR *dir;
    struct dirent *ptr;
    int count = 0;
    char temp[PATH_MAX+1];

    //获取该目录下文件总数和最长的文件名
    dir = opendir(path);
    if(NULL==dir){
        if(errno==13){
            printf("权限不足,无法打开%s\n",path);
            return;
        }
        else
            my_err("opendir",__LINE__);
    }

    while((ptr = readdir(dir))!=NULL){
        if(g_maxlen<strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }
    closedir(dir);

    //if(count>256)
      // my_err("too many files under this dir",__LINE__);

    char (*filenames)[PATH_MAX]=(char(*)[PATH_MAX])malloc(sizeof(char)*count*(PATH_MAX+1));  
    int i,j,len=strlen(path);
    //获取该目录下所有的文件名
    dir=opendir(path);
    for(i = 0; i < count; i++)
    {
        ptr=readdir(dir);
        if(ptr==NULL)
        {
            my_err("readdir",__LINE__);
        }
        strncpy(filenames[i],path,len);
        filenames[i][len] = '\0';
        strcat(filenames[i],ptr->d_name);
        filenames[i][len+strlen(ptr->d_name)] = '\0';//将文件名链接到原路径
    }

    //使用冒泡排序法对文件名进行排序，排序后按字母顺序存储于filenames
    for(i=0;i<count-1;i++){
        for(j=0;j<count-1-i;j++){
            if(strcmp(filenames[j],filenames[j+1])>0){
                strcpy(temp,filenames[j+1]);
                temp[strlen(filenames[j+1])]='\0';
                strcpy(filenames[j+1],filenames[j]);
                filenames[j+1][strlen(filenames[j])]='\0';
                strcpy(filenames[j],temp);
                filenames[j][strlen(temp)]='\0';
            }
        }
    }
    if((flag_param & PARAM_R)!=0)    
        printf("%s:\n",path);
    for(i=0;i<count;i++)
    {
        display(flag_param,filenames[i]);    
    }
    //如果命令行中没有-l选项，打印一个换行符
    if((flag_param & PARAM_L) == 0)
        printf("\n");

    //ls -R 
    if((flag_param & PARAM_R)!=0){    
    struct stat buf1 ;
    char test[20];
    char path_temp[PATH_MAX];
    int strl;
    for(i=0;i<count;i++){
        strcpy(path_temp,filenames[i]);
        strcpy(test,filenames[i]+len);
        strl=strlen(filenames[i]);
        if(test[0]=='.')  continue;
        //如果目录文件或目录不存在，报错并退出程序
        if( lstat(path_temp,&buf1)== -1 ){
            if(errno==13)
            {
                printf("没有权限\n");
                return ;
            }
            my_err("stat",__LINE__);
        }
        if( S_ISDIR(buf1.st_mode) ){
            path_temp[strl]='/';
            path_temp[strl+1]='\0';
            display_dir(flag_param,path_temp);
        }    //递归
    }
    }
    free(filenames);
    closedir(dir);

}


int main(int argc , char ** argv)
{
    int i,j,k,num;
    char path[PATH_MAX];
    char param[32];    //保存命令行参数，目录文件名和目录名不在此列
    int  flag_param = PARAM_NONE ;
    struct stat buf ;

    /*命令行参数解析，分析各个选项*/
    j = 0;
    num = 0;
    for(i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            for(k=1;k < strlen(argv[i]); k++,j++)
                param[j]=argv[i][k];  //将所有的参数都保存到数组中
        num++;//'-'的个数
        }
    }

    /*所支持的参数*/
    for(i=0; i<j; i++)
    {
        if(param[i] == 'a'){
            flag_param |= PARAM_A;
            continue;
        }else if(param[i] == 'l'){
            flag_param |= PARAM_L;
            continue;
        }else if(param[i]=='R'){
            flag_param |= PARAM_R;
            continue;
        }else{
            printf("my_ls: invalid option -%c\n",param[i]);
            exit(1);
        }
    }
    param[j] = '\0';

    //如果没有输入文件名或目录，就显示当前目录
    if((num+1) == argc){
        strcpy(path,"./");
        path[2]='\0';
        display_dir(flag_param,path);
        return 0;
    }

    for(i=1;i<argc;i++)    
    {
        //如果不是目录文件名或者目录，解析下一个命令参数
        if(argv[i][0] =='-'){
            continue;
        }
        else{
            strcpy(path,argv[i]);
        }

        //如果目录文件或目录不存在，报错并退出程序
        if( stat(path,&buf)== -1 ){
            my_err("stat",__LINE__);
        }

        if( S_ISDIR(buf.st_mode) ) //argv[i]是一个目录
            //如果最后一个字符不是'/',就加上'/'
        {
            if(path[strlen(argv[i])-1]!='/'){
                path[strlen(argv[i])]='/';
                path[strlen(argv[i])+1]='\0';
            }
            else{
                path[ strlen(argv[i]) ] = '\0';
            }
            display_dir(flag_param,path);           
        }
        else{
            display(flag_param,path);
        }
    }
    return 0;
}

