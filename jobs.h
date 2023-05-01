#include <sys/types.h>
#include "list.h"
#ifndef _JOBS_H
#define _JOBS_H
    void fg(StackP*, pid_t);
    void jobs(StackP);
#endif