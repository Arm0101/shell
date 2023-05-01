#include <stdio.h>
#include <string.h>
#include "help.h"

char PATH[1024];
void set_help_dir(char * path){
    strcpy(PATH,path);
    strcat(PATH,"/helps/");
}

void help(char * keyword){
    char path[1024];
    strcpy(path,PATH);
    if (keyword == NULL){
        strcat(path,"main.help");
    }
    else{
        strcat(path,keyword);
        strcat(path,".help");
    }
    FILE *file = fopen(path,"r");
    if (file == NULL){
        fprintf(stderr,"Error al abrir el archivo %s\n", path);
        return;
    }
    char line[1024];
    while (fgets(line,1024,file))
    {
        printf("%s", line);
    }
    printf("\n");
    fclose(file);
}
