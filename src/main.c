#include <stdio.h>
#include <stdlib.h>
#include "LibFunction/readLineShell.h"
#include "LibFunction/parsingLineShell.h"

#define EXIT_CODE 0
#define BUF_SIZE 128
#define TOKEN_SEP " \t\n\r"

void shellCycle(){
    char *line = readLine();
    char *tokenTab[BUF_SIZE];
    int arg;

    while(line != NULL){
        arg = parsingLine(line, tokenTab);
        free(line);
        line = readLine();
    }
}


int main(){
    shellCycle();
    return EXIT_CODE;
}