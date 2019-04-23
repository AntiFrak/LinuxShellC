#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


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