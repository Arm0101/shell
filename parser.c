#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>


#include "list.h"
#include "parser.h"
#include "utils.h"

char** list_args(const char *, size_t *);

void redir_files(const char*, char **, char **, bool *);
void remove_redir (char *);

command parse_command(const char *line){
    char* _line = strdup(line);
    
    command temp;
    //info del comando
    size_t size = 0;
    char **args = NULL;
    char* name = NULL;
    char *inf = NULL, *outf = NULL;
    bool replace  = false;

     //obtener el nombre del comando
     for (size_t i = 0; i < strlen(_line); i++)
     { 
         if (_line[i] == ' ' || _line[i] == '\0') break;
         _strcat(&name, _line[i]);
     }


    //obtener la lista de argumentos;
    char * c = strchr(_line, ' ');
    if (c != NULL){

        redir_files(c, &inf,&outf, &replace);
        if (inf!= NULL || outf != NULL){
          remove_redir(c);
        }
        args = list_args(c, &size);
    }

    free(_line);
    temp.name = name;
    temp.args = args;
    temp.n_args = size;
    temp.outFile = outf;
    temp.inFile = inf;
    temp.replace_content = replace;

    return temp;
}

void parse_line(const char* line){
    char* _line = strdup(line);
    char * l = strchr(_line,'#');
    if (l != NULL)
        *l = '\0';
    puts(_line);
}

void remove_redir (char * c){
    //se quita de los argumentos
    while (*c != '\0')
    {
        if (*c == '>' || *c == '<'){
            *c = '\0';
        }
        c++;
    }
}
void redir_files(const char* args, char ** inf, char **outf, bool * rep){
    char* _args = strdup(args);
    if (_args != NULL && trim(_args) != NULL)
        _args = trim(_args);

    char * _if = NULL;
    char * _of = NULL;

    bool is_if = false; 
    bool is_of = false;
    bool is_replace = false;
    
    for (size_t i = 0; i < strlen(_args); i++)
    {
        if (is_if && _args[i] != '>'){
            _strcat(&_if, _args[i]);
        }
         if (is_of && _args[i] != '<'){
            _strcat(&_of, _args[i]);
        } 


        if (_args[i] == '<'){
            is_if = true;
            is_of = false;
        }
        if (_args[i] == '>'){
            is_replace = true;
            is_of = true;
            is_if = false;

            if ((i+1) < strlen(_args)){
                if (_args[i + 1] == '>'){
                    is_replace = false;
                    i++;
                }
            }
        }
        
    }
     if (_if != NULL){
         *inf = realloc(*inf, strlen(_if));
          strcpy(*inf,_if);
     }

     if (_of != NULL){
         *outf = realloc(*outf, strlen(_of));
          strcpy(*outf,_of);
     }
    *rep = is_replace;

    free(_args);
    free(_if);
    free(_of); 
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

