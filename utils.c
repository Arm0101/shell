
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include "utils.h"
void _strcat(char** s, const char c){
    ssize_t len;
     if (*s == NULL) len = 1;
     else  len = strlen(*s) + 1;

    *s = realloc(*s, len); 
    
    char temp[2];
    temp[0] = c;
    temp[1] = '\0';
    
    strcat(*s,temp);
       
}
char* trim(const char * string){
    char * new_string = NULL;
    for (size_t i = 0; i < strlen(string); i++)
    {
        if (string[i] == ' ') continue;
        _strcat(&new_string, string[i]);
    }
    return new_string;
}
