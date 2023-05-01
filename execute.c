
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "execute.h"
#include "list.h"
#include "parser.h"
#include "utils.h"
#include "jobs.h"
#include "help.h"
#define ACCESS_FLAGS S_IRUSR| S_IWUSR | S_IXUSR
#define READ_END 0
#define WRITE_END 1

void print_status(int);
void exec(pline,StackP*);
pid_t execute_cmd(command c, int in_fd, int out_fd, int ** fd, int n_cmd){
    pid_t pid = fork();
    if (pid < 0){
        perror("Error al crear el proceso");
        exit(EXIT_FAILURE);
    }
    if (pid == 0){

        if(!strcmp(c.name, "cd")){
            exit(EXIT_SUCCESS);
        }
        if(!strcmp(c.name, "fg")){
            exit(EXIT_SUCCESS);
        }
        if(!strcmp(c.name, "jobs")){
            exit(EXIT_SUCCESS);
        }
        if(!strcmp(c.name, "true")){
            exit(EXIT_SUCCESS);
        }
        if(!strcmp(c.name, "help")){
            exit(EXIT_SUCCESS);
        }
         if(!strcmp(c.name, "false")){
            exit(EXIT_FAILURE);
        }
        if (c.outFile != NULL){
            int flags = O_WRONLY | O_TRUNC |O_CREAT;
            if (!c.replace_content)
                flags = O_WRONLY | O_CREAT | O_APPEND;

           int fd1 = open(c.outFile, flags, ACCESS_FLAGS);
           if (fd1 == -1){
                perror("open");
                exit(EXIT_FAILURE);
           }
           dup2(fd1, STDOUT_FILENO);
           close(fd1);
        }
        if (c.inFile != NULL){
            int fd2 = open(c.inFile, O_RDONLY,0);
            if (fd2 == -1){
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd2, STDIN_FILENO);
            close(fd2);
        }

        //fd pipes

        if (in_fd != -1){
            dup2(in_fd, STDIN_FILENO);
        }
        if (out_fd != -1){
            dup2(out_fd, STDOUT_FILENO);
        }
        if (fd != NULL){
            for (int i = 0; i < n_cmd; i++)
            {
                close(fd[i][READ_END]);
                close(fd[i][WRITE_END]);
            }
            
        }
        //ejecutar binario 
        execvp(c.name, c.args);
        perror("No se pudo ejecutar");
        exit(EXIT_FAILURE);
    }
    return pid;
}

void execute_line(pline l, StackP* st, char * line){
    if (l.background){
        pid_t pid = fork();
        if (pid < 0){
            perror("Error al crear el proceso");
            return;
        }
        if(pid == 0){
            exec(l,st);
            exit(EXIT_SUCCESS);
        }
        printf("proceso: %d\n", pid);
        stack_push(st,pid,line);
    }
    else{
        exec(l,st);
    }
}
void exec(pline l,StackP* st){
    int status = 0;
    int chain = 0;

    for (size_t i = 0; i < l.n_commands; i++)
    {
        if (l.n_pipes[i] == 0){
            
            if (!strcmp(l.comands[i][0].name,"cd")){
                status = cd(l.comands[i][0].args[1]);

            } else if (!strcmp(l.comands[i][0].name,"exit")){
                exit(EXIT_SUCCESS);
            } else if (!strcmp(l.comands[i][0].name,"fg")){
                if (l.comands[i][0].args[1] == NULL){
                    fg(st,-1);
                }
                else{
                    pid_t _p = atoi(l.comands[i][0].args[1]);
                    fg(st,_p);
                }
            }else if (!strcmp(l.comands[i][0].name,"jobs")){
                    jobs(*st);
            } else if (!strcmp(l.comands[i][0].name,"help")){
                    help(l.comands[i][0].args[1]);
            }
            else{
                pid_t pid = execute_cmd(l.comands[i][0],-1,-1, NULL, 0);
                waitpid(pid,&status,0);
            }
        }
        else{
            status = execute_pipes(l.comands[i],l.n_pipes[i]);
        }
        if (l.chains != NULL && chain < strlen(l.chains)){
            if (l.chains[chain] == '|'){
                if (status == EXIT_SUCCESS){
                    return;
                }
            }
             if (l.chains[chain] == '&'){
                if (status != EXIT_SUCCESS)
                    return;
            }
            chain++;
        }
        
    }
}

int execute_pipes(command * cmds, int n_pipes){
         bool fail = false;
         int **fd = malloc(sizeof(int *) * n_pipes);
         pid_t pids[n_pipes+1];
         int _pipe = 0;
         //crear los pipes
         for (int i = 0; i < n_pipes ; i++)
         {
            fd[i] = malloc(sizeof(int) * 2);
            int p = pipe(fd[i]);
            if (p == -1){
                perror("error pipe");
                return EXIT_FAILURE;
            }
         }
         
         for (int i = 0; i <= n_pipes; i++)
         {
            int in_fd;
             int out_fd;

             if (i == 0){
                //si es el primer cmd redirige la salida al extremo de escritura
                 in_fd = -1;
                 out_fd = fd[_pipe][WRITE_END];
             
             }else if (i == n_pipes){
                //si es el ultimo cmd redirige la entrada al extremo de lecutura
                 in_fd = fd[_pipe][READ_END];
                 out_fd = -1;
             }
             else {
                //si es un cmd intermedio
                 in_fd = fd[_pipe][READ_END];
                 out_fd = fd[++_pipe][WRITE_END];

             }

             pids[i] = execute_cmd(cmds[i],in_fd,out_fd, fd, n_pipes);
         }
         for (int i = 0; i < n_pipes; i++)
         {
             close(fd[i][READ_END]);
             close(fd[i][WRITE_END]);
         }
         for (int i = 0; i <= n_pipes; i++)
         {
             int status = 0;
             waitpid(pids[i],&status,0);
             if (WIFEXITED(status)){
                 int stat = WEXITSTATUS(status);
                 if (stat != 0)
                    fail = true;
            }
         }
         return fail ? EXIT_FAILURE : EXIT_SUCCESS;
 }

int cd(const char* dir){
    int e;
    if (dir == NULL){
        e = chdir(getenv("HOME"));
    }
    else {
        e = chdir(dir);
    }

    if (e == -1) {
        perror("error");
       return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void print_status( int status){
    if (WIFEXITED(status)){
        int stat = WEXITSTATUS(status);
        if (stat != 0)
            printf("\nstatus %d\n", stat);
    }
}