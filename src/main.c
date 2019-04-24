#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "LibFunction/functionLineShell.h"
#include "LibFunction/functionCommandsShell.h"

#define EXIT_CODE 0
#define BUF_SIZE 10

int flagBackground = 0;
int flagFile = 0;
int flagExit = 0;

void executeCommand(int number,char *tokenTab[]);
void executeCommandOnFile(int number, char *tokenTab[]);

char *command[] = {
    "cd",
    "touch",
    "mkdir",
    "exit"
};

int commands(char *tokenTab[]){
    if(strcmp(tokenTab[0], command[0])==0){
        changeDir(tokenTab);
        return 2;
    }
    if((strcmp(tokenTab[0], command[1]))==0){
        touchFile(tokenTab);
        return 2;
    }
    if((strcmp(tokenTab[0], command[2]))==0){
        makeDir(tokenTab);
        return 2;
    }
    
    if((strcmp(tokenTab[0],command[3]))==0){
        flagExit = 1;
        return 2;
    }
    return 1;
}


void shellCycle(){
    char *line = readLine();
    char *tokenTab[BUF_SIZE];
    int number, func;
    
    while(flagExit != 1){
        number = parsingLine(line, tokenTab, &flagBackground, &flagFile);
        func = commands(tokenTab);
        if(func == 1){
            if(flagFile == 0){
                executeCommand(number, tokenTab);
            }
            else{
                executeCommandOnFile(number,tokenTab);
            }
        }
        free(line);
        flagFile = 0;
        if(flagExit == 0){
            line = readLine();
        }
    }
}

int main(){
    
    shellCycle();
    return EXIT_CODE;
}


void executeCommand(int number, char *tokenTab[]){
    pid_t pid;
    int  wstatus;
    char *argv[number];

    for(int i = 1; i < number; i++){
        argv[i] = tokenTab[i];
    }
    
    argv[0]= tokenTab[0];
    argv[number] = NULL;

    pid = fork();
    if(pid == -1){
        perror("fork1");
        exit(-1);
    }
    if(pid == 0){
        if(execvp(tokenTab[0],argv)== -1){ 
        perror("execvp");
        }
        exit(-1);
    }
    else{
        if(flagBackground == 0){
            waitpid(pid, &wstatus, 0);
        }
        else{
            printf("~~~~~ Process running in in Background. PID:%d\n",pid);
        }
            
    }
    flagBackground = 0;
    pid = 0;
}



void executeCommandOnFile(int number, char *tokenTab[]){
    pid_t pid;
    int wstatus;
    char *argv[number-1];
    
    char *fileName = tokenTab[number];
    
    int fds[2];
    int file;

    

    for(int i = 0; i < number-1; i++){
        argv[i] = tokenTab[i];
    }
  
    pipe(fds);
    pid = fork();
    if(pid == -1){
        perror("fork1");
        exit(-1);
    }
    if(pid == 0){
        file = open(fileName, O_CREAT | O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
        if (file == -1) {
            perror ("open"); 
            exit(-1); 
            }

        close(fds[1]);
        dup2(file, 1);

        if(execvp(tokenTab[0],argv)== -1){ 
            perror("execvp");
            exit(-1);
        }
    }
    else{
           
        close(fds[0]);
        waitpid(pid, &wstatus, 0);
    }
}