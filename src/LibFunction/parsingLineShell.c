#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 100
#define TOKEN_SEP " \t\n\r"

char* parsing(char string[], char delim[]){
    
    char *ptr = string;
    int flag = 0;

    if (delim == NULL){
        return string;
    }

    if(flag == 1){
        return NULL;
    }

    char *ptrRet = ptr;
    for(int j = 0; ptr != '\0'; j++){
        for(int i =0; delim[i] != '\0'; i++){
            if(ptr[j] == '\0'){
                flag =1;
                return ptrRet;
            }
            if(ptr[j] == delim[i]){
                ptr[j]= '\0';
                ptr += j+1;
                return ptrRet;
            }
        }
    }
    return NULL;
}

char **parsingLine(char *line){
    int bufsize = BUF_SIZE;
    char **token = malloc(bufsize *sizeof(char*));
    char *tokenTab;
    int pos;

    if (!token){
        perror("Bled wydzelenia pameci");
        return 1;
    }

    token = parsing(line, TOKEN_SEP);
    for(pos = 0; token != NULL; pos++){
        tokenTab[pos] = token;
        if(pos >= bufsize){
            bufsize +=BUF_SIZE;
            tokenTab= realloc(tokenTab, bufsize * sizeof(char*));
            if (!token){
                perror("Bled wydzelenia pameci");
                return 1;
            }
        }
        token = parsing(NULL, TOKEN_SEP);
    }
    tokenTab[pos] = NULL;
    return tokenTab;
}

int main(){
    char tab[100] = "yan cdv yhnds";
    char **ppt = parsingLine(tab);
    while(ppt!=NULL){
        printf(ppt);
    }
    return 0;
}