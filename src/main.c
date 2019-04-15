#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "LibFunction/readLineShell.h"
#include "LibFunction/parsingLineShell.h"

#define EXIT_CODE 0
#define BUF_SIZE 128

void executeCommand(int number,char *tokenTab[]);

void shellCycle(){
    char *line = readLine();
    char *tokenTab[BUF_SIZE];
    int number, stat;

    while(line != NULL){
        number = parsingLine(line, tokenTab);
        executeCommand(number, tokenTab);
        free(line);
        line = readLine();
    }
}

int main(){
    shellCycle();
    return EXIT_CODE;
}

void executeCommand(int number, char *tokenTab[]){
    pid_t pid;
    int  wstatus;
    char *argv[number+1];
   
	
    if (number == 1) 
    {
        argv[1] = '\0';
    }
    else 
    {
        for(int i = 1; i<number; i++){
		    argv[i] = tokenTab[i];
	    }   
    }
    
    argv[number+1] = '\0';

    pid = fork();
    if(pid == -1){
        perror("fork1");
        exit(-1);
    }
    if(pid == 0){
                     
        if(execvp(tokenTab[0], argv)== -1){ 
            perror("execvp");
        }
         exit(-1);
    }
        
            
    while((pid=wait(&wstatus)) != -1){}
    
}
