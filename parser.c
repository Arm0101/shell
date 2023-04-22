#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"
#include "parser.h"
#include "utils.h"

char **list(const char *, size_t *, const char*);
void setCommand(command *, const char*, char **, int , const char*, const char*, bool);
command *setCMDS(char ** cmds, size_t n_cmds);
void redir_files(const char *, char **, char **, bool *);
void remove_redir(char *);

command parse_command(const char *line)
{
    char *_line = strdup(line);

    command temp = (command){0, NULL, NULL, NULL, NULL, false};
    // info del comando
    size_t size = 0;
    char **args = NULL;
    char *name = NULL;
    char *inf = NULL, *outf = NULL;
    bool replace = false;

    // obtener la lista de argumentos;
    char *c = strchr(_line, ' ');
    if (c != NULL) {

     redir_files(c, &inf, &outf, &replace);
        if (inf != NULL || outf != NULL){
          remove_redir(c);
        }
     }
    args = list(_line, &size," ");
    args = list_add(args, NULL, &size);
    setCommand(&temp,args[0],args,size,outf,inf,replace);
    free(_line);
    return temp;
}

void setCommand(command * c, const char* name, char ** args, int n_args, const char* outf, const char* inf, bool replace){

    c->name = malloc (strlen(name) * sizeof(char));
    strcpy(c->name,name);
    c->args = args;
    c->n_args = n_args;

    if(outf != NULL){
        c->outFile = malloc (strlen(outf) * sizeof(char));
        strcpy(c->outFile,outf);
    }

    if (inf != NULL){
        c->inFile = malloc (strlen(inf) * sizeof(char));
        strcpy(c->inFile, inf);
    }

    c->replace_content = replace;
}

pline parse_line(const char *line)
{

    pline temp = (pline) {0, NULL};
    size_t n = 0;
    char *_line = strdup(line);
    char *l = strchr(_line, '#');
    char** _cmds = NULL;
    //quitar #...
    if (l != NULL)
        *l = '\0';

    // dividir por |
    _cmds = list(_line,&n, "|");
    
    command * cmds = setCMDS(_cmds, n);
    temp.n_c = n;
    temp.comands = cmds;

     free(_cmds);
     free(_line);
    return temp;
   
}

void remove_redir(char *c)
{
    // se quita de los argumentos
    while (*c != '\0')
    {
        if (*c == '>' || *c == '<')
        {
            *c = '\0';
        }
        c++;
    }
}
void redir_files(const char *args, char **inf, char **outf, bool *rep)
{
    char * _args = trim(strdup(args));
    char _if[strlen(_args)] ;
    char _of[strlen(_args)] ;
    int len1 = 0;
    int len2 = 0;
    bool is_if = false;
    bool is_of = false;
    bool is_replace = false;

    for (size_t i = 0; i < strlen(_args); i++)
    {
        if (is_if && _args[i] != '>')
        {
            _if[len1] = _args[i];
            len1++; 
        }
        if (is_of && _args[i] != '<')
        {
          _of[len2] = _args[i];
          len2++;
        }

        if (_args[i] == '<')
        {
            is_if = true;
            is_of = false;
        }
        if (_args[i] == '>')
        {
            is_replace = true;
            is_of = true;
            is_if = false;

            if ((i + 1) < strlen(_args))
            {
                if (_args[i + 1] == '>')
                {
                    is_replace = false;
                    i++;
                }
            }
        }
    }
    if (len2 > 0) {
        *outf = strndup(_of, len2);
    }
    if (len1 > 0) {
        *inf = strndup(_if, len1);
    }
    
    *rep = is_replace;
     free(_args);
}

char **list(const char *args, size_t *size, const char* s)
{
    char *_args = strdup(args);
    char **l_args = NULL;

    char *token = strtok(_args, s);
    while (token != NULL)
    {
        l_args = list_add(l_args, token, size);
        token = strtok(NULL, s);
    }
    free(token);
    free(_args);
    return l_args;
}

command *setCMDS(char ** cmds, size_t n_cmds){
     command * temp = malloc(sizeof(command) * n_cmds);
     for (size_t i = 0; i < n_cmds; i++)
     {
        temp[i] = parse_command(cmds[i]);
     }
     
     return temp;
}