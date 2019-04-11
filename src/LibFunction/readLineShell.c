#include <stdio.h>

char *readLine(){
    char *SHstring = NULL;
    size_t buffer = 0;
    getline(&SHstring, &buffer, stdin);
    return SHstring;
}