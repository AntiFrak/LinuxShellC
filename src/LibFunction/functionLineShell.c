#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_SEP " \n\t\r"

int parsingLine(char *line, char *tokenTab[], int *flag){
    char *token;
    int pos = 0;
    token = strtok(line, TOKEN_SEP);
    while(token != NULL){
        tokenTab[pos] = token;
        token = strtok(NULL, TOKEN_SEP);
        pos++;
    }
    for(int i = 0; i<pos; i++){
        if(strcmp(tokenTab[i],"&") == 0){
            *flag = 1;
            tokenTab[i] = NULL;
            pos--;
        }
    }
    return pos;
}

char *readLine(){
    fflush(stdout);
    char *SHstringCopy, *SHstring = NULL;
    size_t buffer = 0;
    printf("---->");
    getline(&SHstring, &buffer, stdin);
    return SHstring;
}