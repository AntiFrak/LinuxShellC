#include <stdio.h>
#include <stdlib.h>
#include "LibFunction/readLineShell.h"
#include "LibFunction/parsingLineShell.h"

#define EXIT_CODE 0
#define BUF_SIZE 100
#define TOKEN_SEP " \t\n\r"

void shellCycle(){
    char *line;
    char **arg;
    do{
        printf("---->");
        line = readLine();
        arg = parsingLine(line);
        
        free(line);
        free(arg);
    }while(1);
}


int main(){
    //shellCycle();
    char * line;
    char **arg;
    line = readLine();
    arg = parsingLine(line);
    for(int i =0; i<100; i++){
        printf(arg[i]);
    }
    free(line);
    free(arg);
    return EXIT_CODE;
}