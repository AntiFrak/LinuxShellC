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
    pid_t pid, wpid;
    int  wstatus;
    char *argv[2]; // для поиска ебучего бага
    argv[1]=NULL;// для поиска ебучего бага

   
    //for(int i = 0; i< number; i++){
        argv[0]= tokenTab[0];
        pid = fork();
        if(pid == 0){
            if(execvp(tokenTab[0], argv)== -1){  // тепер эта хуйня срабатывает когда вписываеться два параметра нп firefox &, top &
                perror("execvp");
                exit(-1);
            }
        }
        if(pid < 0){
            perror("fork2");
        }
        else{
            do{
                wpid = waitpid(pid, &wstatus, WUNTRACED);
            }while(!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
        }
   // }
    
}

