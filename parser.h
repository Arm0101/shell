
#ifndef _PARSER_H
#define _PARSER_H

    typedef struct{
        int n_args;
        char ** args;
        char *name;
    } command;

   void parse_command(const char *);

#endif