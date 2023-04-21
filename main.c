#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "list.h"
#include "parser.h"


int main(){  
    char * line = NULL;
    size_t len;
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
        if (c.inFile != NULL)
            printf("%s\n",c.inFile);
        if (c.outFile != NULL)
            printf("%s\n",c.outFile);
        printf("%d\n", c.replace_content);
        if (c.args != NULL)
            print_list(c.args, c.n_args);

    }
}