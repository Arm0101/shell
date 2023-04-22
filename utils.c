
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "utils.h"
#include "list.h"

char* trim(const char * string){
    char temp[strlen(string)];
    int index = 0;
    for (size_t i = 0; i < strlen(string); i++)
    {
        if (string[i] == ' ') continue;
        temp[index++] = string[i]; 
    }
    return strndup(temp, index);
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