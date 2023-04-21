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
        int n_c;
        command* comands;
    } pline;
    
   command parse_command(const char *);
   void parse_line(const char *);

#endif