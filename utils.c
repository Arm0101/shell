
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "utils.h"
#include "list.h"

void _strcat(char** s, const char c){
    ssize_t len;
     if (*s == NULL) len = 1;
     else  len = strlen(*s) + 1;

    *s = realloc(*s, len); 

    char temp[2];
    temp[0] = c;
    temp[1] = '\0';

    strcat(*s,temp);
       
}
char* trim(const char * string){
    char * new_string = NULL;
    for (size_t i = 0; i < strlen(string); i++)
    {
        if (string[i] == ' ') continue;
        _strcat(&new_string, string[i]);
    }
    return new_string;
}

void info(command c){
    printf("------------------info-------------------\n");
      printf("name: %s \n", c.name);
      if (c.inFile != NULL){
            printf("IN: ");
            printf("%s\n",c.inFile);
      }
      if (c.outFile != NULL){
             printf("Out: ");
             printf("%s\n",c.outFile);
            printf("Replace: %d\n", c.replace_content);
      }

        
       
    if (c.args != NULL){
        printf("args: \n");
        print_list(c.args, c.n_args);
    }
    printf("------------------------------------------------------\n");
}