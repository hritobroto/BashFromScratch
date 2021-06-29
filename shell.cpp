#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <bits/stdc++.h>
#include <curses.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#define clrscr() printf("\e[1;1H\e[2J")
#define DELIMS " \t\r\n"
int pos=0;
int back=0;
int front=0;
void cat_commW(char (*comm)[500])
{
        FILE *fp;
        char ch[100];
        int d=0;
        for(int i=4;i<strlen(*comm);i++)
            ch[d++]=(*comm)[i];
        fp=fopen(ch,"a");
        for(;;)
        {
            char c[100];
            fgets(c,100,stdin);
            fputs(c,fp);
            if(c[strlen(c)-2]=='.')
                break;
        }
        fclose(fp);
}
void make_dr(char (*comm)[500])
{
    char dirname[100];
    int i=0,d=0;
    for(i=6;i<strlen(*comm);i++)
        dirname[d++]=(*comm)[i];
    mkdir(dirname,0777);
}
void remov_dr(char (*comm)[500])
{
    char dirname[100];
    int i=0,d=0;
    for(i=6;i<strlen(*comm);i++)
        dirname[d++]=(*comm)[i];
    rmdir(dirname);
}
void cat_commR(char (*comm)[500])
{
        FILE *fp;
        char ch[100],c;
        int d=0;
        //printf("Reading file\n");
        for(int i=4;i<strlen(*comm);i++)
            ch[d++]=(*comm)[i];
        //printf("%s\n",ch);
        fp=fopen(ch,"r");
        while ((c = getc(fp))!=EOF) 
            printf("%c",c);
        fclose(fp);
}
void cd_comm(char (*comm)[500])
{
    char chd[200]="";
    char chd2[100]="";
    int i,d=0;
    strcat(chd,"/home/hritobroto/");
    for(i=3;i<strlen(*comm);i++)
        chd2[d++]=(*comm)[i];
    //printf("%s\n",chd);
    strcat(chd,chd2);
    //printf("%s\n",chd);
    chdir(chd);
}
void ls_comm(char (*comm)[500])
{
    //printf("%c\n",cmd[0]);
    char *token=strtok((*comm)," ");
    while(token!=NULL)
    {
        //printf("%s\n",token);
        if(strcmp(token,"-l")==0)
        {
            char* arg[]={"ls","-l",NULL};
            execvp("ls",arg);
        }
        if(strcmp(token,"-al")==0)
        {
            char* arg[]={"ls","-al",NULL};
            execvp("ls",arg);
        }
        if(strcmp(token,"-m")==0)
        {
            char* arg[]={"ls","-m",NULL};
            execvp("ls",arg);
        }
        if(strcmp(token,"-r")==0)
        {
            char* arg[]={"ls","-r",NULL};
            execvp("ls",arg);
        }
        if(strcmp(token,"-d")==0)
        {
            char* arg[]={"ls","-d",NULL};
            execvp("ls",arg);
        }
        if(strcmp(token,"-a")==0)
        {
            char* arg[]={"ls","-a",NULL};
            execvp("ls",arg);
        }
        token=strtok(NULL," ");
    }
}
void readComm(char cmd[],char *par[])
{
    char *line;
    int count=0,i=0,j=0;
    char *array[100],*pch;
    //Read one line
    /*for(;;)
    {
        int c=fgetc(stdin);
        line[count++]=(char)c;
        if(c=='\n')
            break;
    }*/
    char pa[100]="\033[0;32mOrion@Bash\033[0m:\033[0;36m~";
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    strcat(pa,cwd);
    char st[10]="\033[0m$ ";
    strcat(pa,st);
    line=readline(pa);
    add_history(line);
    if(count==1)
        return;
    pch=strtok(line,"\n");
    while(pch!=NULL)
    {
        array[i++]=strdup(pch);
        pch=strtok(NULL,"\n");
    }
    strcpy(cmd,array[0]);
    for(int j=0;j<i;j++)
        par[j]=array[j];
    par[i]=NULL;
}

/*void clear_screen()
{
    static int ft=1;
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    if(ft)
    {
        /*const char* CLEAR_SCREEN_ANSI="\e[1;1H\e[2J";
        write(STDOUT_FILENO,CLEAR_SCREEN_ANSI,12);
        
        ft=0;
        //system("clear");
    }
    printf("\033[0;32m");
    printf("Orion@Bash:");
    printf("\033[0m");
    printf(":");
    printf("\033[0;36m");
    printf("~%s$ ",cwd);
    printf("\033[0m");
}*/
int prev_history(int a,int b)
{
    //printf("hello\n");
    /*history_set_pos(0);
    int lin=(int)*previous_history;
    printf("%d\n",current_history);*/
    HISTORY_STATE *myhist = history_get_history_state();
    HIST_ENTRY **mylist = history_list ();
    pos=myhist->length-1;
    if((pos-back)>=0)
    {
        printf ("%s\n",mylist[pos-back]->line);
        back++;
    }
    else
    {
        printf("End\n");
        front=0;
        back=0;
    }
    front=back;
    rl_on_new_line ();
    return 0;
}
int nex_history(int a,int b)
{
    //printf("hello\n");
    /*history_set_pos(0);
    printf("%s\n",next_history);*/
    HISTORY_STATE *myhist = history_get_history_state();
    HIST_ENTRY **mylist = history_list ();
    pos=myhist->length-1;
    if((pos+front)<myhist->length)
    {
        printf ("%s\n",mylist[pos+front]->line);
        front++;
    }
    else
    {
        printf("End\n");
        back=0;
        front=0;
    }
    back=front;
    rl_on_new_line ();
    return 0;
}
void disp_history()
{
    HISTORY_STATE *myhist = history_get_history_state();
    //printf("yo\n");
    /*register HIST_ENTRY **the_list;
    register int i;
    the_list = history_list ();command,"ping")==0
    if (the_list)
    for (i = 0; the_list[i]; i++)
    rintf ("%s\n",the_list[i]->line);*/
    HIST_ENTRY **mylist = history_list ();
    register int i;
    for (int i = 0; i < myhist->length; i++) 
    { /* output history list */
        printf ("%d %s\n",i + history_base ,mylist[i]->line);
    }
}
void ping_add(char (*comm)[500])
{
    //printf("%c\n",cmd[0]);
    //char *token=strtok((*comm)," ");
    char add[100];
    int d=0;
    for(int i=5;i<strlen(*comm);i++)
            add[d++]=(*comm)[i];
    //printf("%s\n",token);  
    printf("%s\n",add);
    char* arg[3]={"ping","",NULL};
    arg[1]=add;
    execvp(arg[0],arg);
}
int main()
{
    clrscr();
    char cmd[500], command[500], *parameters[50];
    //environment variable
    char *envp[]={ (char *) "PATH=/bin",0};
    using_history();
    rl_command_func_t prev_history;
    rl_command_func_t nex_history;
    rl_bind_keyseq("\e[D", rl_backward_char);
    rl_bind_keyseq("\e[C", rl_forward_char);
    //rl_bind_keyseq("\e[A", nex_history);
    //rl_bind_keyseq("\e[B", prev_history);
    //rl_bind_keyseq("\\C-i", rl_complete);
    int quit=0;
    while(!quit)
    {
        char cmd[500], command[500], *parameters[50];
        //environment variable
        char *envp[]={ (char *) "PATH=/bin",0};
        //displaying prompt on screen
        //clear_screen();
        //read input from user
        readComm(command,parameters);
        if(fork()!=0)
            wait(NULL);
        else
        {
            strcpy(cmd,"/bin/");
            strcat(cmd,command);
            //printf("%s\n",cmd);
            //printf("%s\n",command);
            
            //ADD HISTORY
            /*char *expansion;
            int result;
            result = history_expand (command, &expansion);*/
            //append_history(1,"history_file");
            /*strncpy (command, expansion, sizeof (command));
            free (expansion);*/
        
            if(command[0]=='l' && command[1]=='s' && strlen(command)>2)
                ls_comm(&command);
            else if(strcmp(command,"history")==0)
                disp_history();
            else if(command[0]=='c' && command[1]=='d')
                cd_comm(&command);
            else if(command[0]=='c' && command[1]=='a' && command[2]=='t' && command[3]=='>')
            {
                cat_commW(&command);
                break;
            }
            else if(command[0]=='c' && command[1]=='a' && command[2]=='t' && command[3]==' ')
            {
                cat_commR(&command);
                break;
            }
            else if(command[0]=='p' && command[1]=='i' && command[2]=='n' && command[3]=='g')
                ping_add(&command);
            else if(command[0]=='m' && command[1]=='k' && command[2]=='d' && command[3]=='i' && command[4]=='r')
                make_dr(&command);
            else if(command[0]=='r' && command[1]=='m' && command[2]=='d' && command[3]=='i' && command[4]=='r')
                remov_dr(&command);
            else if(strcmp(command,"pwd")==0)
            {
                char* arg[]={"pwd",NULL};
                execvp("pwd",arg);
            }
            else if(strcmp(command,"clear")==0)
                clrscr();
            else if(strcmp(command,"exit")==0)
                quit=1;
            else
                execve(cmd,parameters,envp);
        }
        if(strcmp(command,"exit")==0)
            quit=1;
    }
    return 0;
}
