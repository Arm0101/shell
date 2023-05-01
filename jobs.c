#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include "list.h"
#include "jobs.h"

void fg(StackP* st, pid_t pid){
    pid_t pid2 = stack_remove(st,pid);
    if (pid2 == -1) return;
    waitpid(pid2,NULL,0);
    
}
void jobs(StackP st){
    for (size_t i = 0; i < st.size; i++)
    {
        printf("%d : %s\n",st.pids[i],st.p_name[i]);
    }
}