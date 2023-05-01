
#include "parser.h"
#include "list.h"
#ifndef _EXECUTE_H
#define _EXECUTE_H

   pid_t execute_cmd(command,int,int,int**,int);
   void execute_line(pline,StackP*,char*);
   int cd(const char *);
   int execute_pipes(command*,int);
#endif