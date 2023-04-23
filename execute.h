
#include "parser.h"
#ifndef _EXECUTE_H
#define _EXECUTE_H

   pid_t execute_cmd(command,int,int,int**,int);
   void execute_line(pline);
   void cd(const char *);
   void execute_pipes(pline);
#endif