
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "execute.h"
#include "list.h"
#include "parser.h"
#include "utils.h"
#define ACCESS_FLAGS S_IRUSR| S_IWUSR | S_IXUSR


void execute_cmd(command c){
    pid_t pid = fork();
    if (pid < 0){
        perror("Error al crear el proceso");
        exit(EXIT_FAILURE);
    }
    if (pid == 0){

        if (c.outFile != NULL){
            int flags = O_WRONLY | O_TRUNC |O_CREAT;
            if (!c.replace_content) 
                flags = O_WRONLY | O_APPEND;

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

        execvp(c.name, c.args);
        perror("No se pudo ejecutar");
        exit(EXIT_FAILURE);
    }
    else {
        int status;
        waitpid(pid,&status,0);
        if (WIFEXITED(status)){
            printf("\nstatus %d\n", WEXITSTATUS(status));
        }

    }
}

void execute_line(pline l){
    info(l.comands[0]);
    execute_cmd(l.comands[0]);
}

