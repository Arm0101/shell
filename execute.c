
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "list.h"

void info(command);
void execute_cmd(command c){

    pid_t pid = fork();
    if (pid < 0){
        perror("Error al crear el proceso");
        exit(EXIT_FAILURE);
    }
    if (pid == 0){

        execvp(c.name, c.args);
        perror("No se pudo ejecutar");
        exit(EXIT_FAILURE);
    }
    else {
        int status;
        waitpid(pid,&status,0);
        if (WIFEXITED(status)){
            printf("status %d\n", WEXITSTATUS(status));
        }

    }
}

void info(command c){
      printf("name: %s \n", c.name);
      if (c.inFile != NULL){
            printf("IN: \n");
            printf("%s\n",c.inFile);
      }
      if (c.outFile != NULL){
             printf("Out: \n");
             printf("%s\n",c.outFile);
      }

    printf("Replace: %d\n", c.replace_content);
        
       
    if (c.args != NULL){
        printf("args: \n");
        print_list(c.args, c.n_args);
    }
}
