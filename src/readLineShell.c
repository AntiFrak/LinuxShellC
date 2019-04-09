#include <stdio.h>

char *readLine(){
    char *SHstring = NULL;
    ssize_t buffer = 0;
    getline(&SHstring, &buffer, stdin);
    return SHstring;
}