
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

char * _strcpy(char * string, int start, int count){
    char * _string = strdup(string);
    
    int len = strlen(_string);
    if (start + count > len || start < 0){
        return (char*) NULL;
    }
    char* str = malloc(sizeof(char)*count + 1);

    for (size_t i = 0; i < count; i++)
    {
        str[i] = _string[start+i];
    }
    str[count] = '\0';
    free(_string);
    return strdup(str);
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