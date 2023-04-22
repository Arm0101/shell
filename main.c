
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "list.h"
#include "parser.h"
#include "execute.h"
void info(command);
int main(){  
    char * line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        printf("my-prompt$ ");
        nread = getline(&line,&len,stdin);
        if (nread == 1 && !strcmp(line, "\n")) continue;
        if (nread == -1) return -1;
                                                                                                                                                                                                                                                                                                                                                                                                                        
        char * l = strchr(line,'\n');
        *l = '\0';
        command c = parse_command(line);
        execute_cmd(c);
    }

}




