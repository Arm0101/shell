#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "parser.h"

char** list_args(const char *, size_t *);
void  _strcat(char** , const char);



void parse_command(const char *line){
    char* _line = strdup(line);
    
    command temp;
    //info del comando
    size_t size = 0;
    char **args = NULL;
    char* name = NULL;

     //obtener el nombre del comando
     for (size_t i = 0; i < strlen(_line); i++)
     { 
         if (_line[i] == ' ' || _line[i] == '\0') break;
         _strcat(&name, _line[i]);
     }
     puts(name);
    
    //obtener la lista de argumentos;
    char * c = strchr(_line, ' ');
    if (c != NULL) args = list_args(c, &size);

    free(_line);
    temp.name = name;
    temp.args = args;
    temp.n_args = size;

    print_list(temp.args, temp.n_args);
}

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

char** list_args(const char *args, size_t *size){
   char* _args = strdup(args);
   char** l_args = NULL;
 
   char* token = strtok(_args, " ");
   while (token != NULL)
   {
     l_args = list_add(l_args,token,size);
     token = strtok(NULL," ");
   }
   free(token);
   free(_args);
   return l_args;
} 
