#include<stdbool.h>
#ifndef _PARSER_H
#define _PARSER_H

    typedef struct{
        int n_args;
        char ** args;
        char *name;
        char *outFile; 
        char *inFile; 
        bool replace_content;
    } command;

    typedef struct
    {
        int n_commands;
        int *n_pipes;
        command** comands;
        char* chains;
        bool background;
    } pline;
    
   command parse_command(const char *);
   pline parse_line(const char *);

#endif