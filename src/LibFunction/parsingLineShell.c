#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128
#define TOKEN_SEP " |"

int parsingLine(char *line, char *tokenTab[]){
    char *token;
    int pos = 0;
    token = strtok(line, TOKEN_SEP);
    while(token != NULL){
        tokenTab[pos] = token;
        token = strtok(NULL, TOKEN_SEP);
        pos++;
    }
    return pos;
}