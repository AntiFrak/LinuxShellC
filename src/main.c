#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include "LibFunction/readLineShell.h"
#include "LibFunction/parsingLineShell.h"

#define EXIT_CODE 0
#define BUF_SIZE 128

void executeCommand(int number,char *tokenTab[]);
void changeDir(char *tokenTab[]);
void touchFile(char *tokenTab[]);
void makeDir(char *tokenTab[]);

char *command[] = {
    "cd",
    "touch",
    "mkdir"
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
    return 1;
}

void shellCycle(){
    char *line = readLine();
    char *tokenTab[BUF_SIZE];
    int number, func;

    while(line != NULL){
        number = parsingLine(line, tokenTab);
        func = commands(tokenTab);
        if(func == 1){
            executeCommand(number, tokenTab);
        }
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
    char *argv[number + 1];

    for(int i = 1; i < number; i++){
        argv[i] = tokenTab[i];
    }

    argv[number+1] = '\0';
    argv[0]= tokenTab[0];
    
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

void changeDir(char *tokenTab[]){
    if(tokenTab[1]== NULL){
        perror("no argument");
        exit(-1);
    }
    else{
        if(chdir(tokenTab[1]) != 0){
            perror("chdir");
            exit(-1);
        }
    }
}

void touchFile(char *tokenTab[]){
    if(tokenTab[1] == NULL){
        perror("No name file");
        exit(-1);
    }
    else{
        if(open(tokenTab[1], O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH) == -1){
            perror("open");
            exit(-1);
        }
    }
}

void makeDir(char *tokenTab[]){
    if(tokenTab[1] == NULL){
        perror("No name derictory");
        exit(-1);
    }
    else{
        if(mkdir(tokenTab[1], 0777)== -1){
            perror("mkdir");
        }
    }
}