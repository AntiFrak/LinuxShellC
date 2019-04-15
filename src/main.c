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
    char *argv[2];
    int pipefd[2];
    int read, write;

    argv[1] = '\0';


   
    for(int i = 0; i< number; i++){
        argv[0]= tokenTab[0];
        if(i>0){
            if((close(write)) == -1){
                perror("close write");
            }
        }

        if(i<number-1){
            if(pipe(pipefd)== -1){
                perror("pipe1");
                exit(-1);
            }
            write = pipefd[1];
        }

        pid = fork();
        if(pid == -1){
            perror("fork1");
            exit(-1);
        }
        if(pid == 0){
            if(i > 0){
                if(dup2(read, STDIN_FILENO) == -1){
                    perror("dup2.1");
                    exit(-1);
                }
                if((close(read)) == -1){
                    perror("close read");
                }
            }
            if(i < number -1){
                if(dup2(write, STDIN_FILENO) == -1){
                    perror("dup2.2");
                    exit(-1);
                }
                if((close(write)) == -1){
                    perror("close write");
            }
            }
            if(execvp(tokenTab[0], argv)== -1){  // тепер эта хуйня срабатывает когда вписываеться два параметра нп firefox &, top &
                perror("execvp");
            }
             exit(-1);
        }
        if(i <number -1){
            read = pipefd[0];
        }
            
    }
    while((pid=wait(&wstatus)) != -1){}
    
}

