/*************************************************************************
	> File Name: 4.c
	> Author: hujialu
	> Mail: 
	> Created Time: 2017年06月24日 星期六 22时24分20秒
 ************************************************************************/


#include <stdio.h> //注意，readline.h中可能需要调用标准IO库的内容，所以stdio.h必须在readline.h之前被包含
#include <readline/readline.h>
#include <readline/history.h>
#include<stdlib.h>

int com_list(char *para)
{
    printf("do com_list:%s\n", para);
    return 0;
}
    
int com_view(char *para)
{
    printf("do com_view:%s\n", para);
    return 0;
}

int com_rename(char *para)
{
    printf("do com_rename:%s\n", para);
    return 0;
}
int com_stat(char *para)
{
    printf("do com_stat:%s\n", para);
    return 0;
}

int com_pwd(char *para)
{
    printf("do com_pwd:%s\n", para);
    return 0;
}
int com_delete(char *para)
{
    printf("do com_delete:%s\n", para);
    return 0;
}
int com_help(char *para)
{
    printf("do com_help:%s\n", para);
    return 0;
}

int com_cd(char *para)
{
    printf("do com_cd:%s\n", para);
    return 0;
}
int com_quit(char *para)
{
    printf("do com_quit:%s\n", para);
    exit(0);
}


typedef struct {
    char *name;            
    rl_icpfunc_t *func;     
    char *doc;           
} COMMAND;

COMMAND commands[] = {
  { "cd", com_cd, "Change to directory DIR" },
  { "delete", com_delete, "Delete FILE" },
  { "help", com_help, "Display this text" },
  { "?", com_help, "Synonym for `help'" },
  { "list", com_list, "List files in DIR" },
  { "ls", com_list, "Synonym for `list'" },
  { "pwd", com_pwd, "Print the current working directory" },
  { "quit", com_quit, "Quit using Fileman" },
  { "rename", com_rename, "Rename FILE to NEWNAME" },
  { "stat", com_stat, "Print out statistics on FILE" },
  { "view", com_view, "View the contents of FILE" },
  { (char *)NULL, (rl_icpfunc_t *)NULL, (char *)NULL }
};


char* dupstr(char *s)
{
  char *r;
  r = malloc (strlen (s) + 1);
  strcpy(r, s);
  return (r);
}
char* stripwhite (char *string)
{
    register char *s, *t;
    
    for (s = string; whitespace (*s); s++)
        ;
    
    if (*s == 0)
        return (s);

    t = s + strlen (s) - 1;
    while (t > s && whitespace (*t))
        t--;

    *++t = '\0';

    return s;
}
COMMAND *find_command (char *name)
{
    register int i;
    
    for (i = 0; commands[i].name; i++)
        if (strcmp (name, commands[i].name) == 0)
            return (&commands[i]);

    return ((COMMAND *)NULL);
}
char* command_generator (const char *text, int state)
{
    static int list_index, len;
    char *name;
    if (!state)
    {
         list_index = 0;
        len = strlen (text);
    }
    while (name = commands[list_index].name)
    {
         list_index++;
    
         if (strncmp (name, text, len) == 0)
             return (dupstr(name));
    }
   return ((char *)NULL);
}
char** fileman_completion (const char *text, int start, int end)
{
    char **matches;
    matches = (char **)NULL;
    if (start == 0)
        matches = rl_completion_matches (text, command_generator);
    return (matches);
}

void initialize_readline ()
{
    rl_readline_name = ">";
    rl_attempted_completion_function = fileman_completion;
}
int main (int argc, char **argv)
{
    char *line, *s;
    initialize_readline();
    for ( ; ;)
    {
        line = readline ("$$>: ");

        if (!line)
            break;
         s = stripwhite (line);
         if (*s)
         {
             add_history(s);
            // execute_line(s);
         }

        free(line);
    }
    exit(0);
}
