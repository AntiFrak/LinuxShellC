#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_SEP " \n\t\r"

// funkcja dzieli string wejsciowy na pojedyncze slowa
// i umieszcza ich do tablicy.
// zwraca dlugosc tej tabeli 
int parsingLine(char *line, char *tokenTab[], int *flagBack, int *flagFile){
    char *token;
    int pos = 0;
    token = strtok(line, TOKEN_SEP);
    while(token != NULL){
        tokenTab[pos] = token;
        token = strtok(NULL, TOKEN_SEP);
        pos++;
    }
    for(int i = 0; i<pos; i++){
        if(strcmp(tokenTab[i],"&") == 0){
            *flagBack = 1;
            tokenTab[i] = NULL;
            pos--;
        }
        else if(strcmp(tokenTab[i],">>") == 0){
            *flagFile = 1;
            tokenTab[i] = tokenTab[i+1];
            tokenTab[i+1] = NULL;
            pos--;
        }
    }
    return pos;
}

//funkcja odczytuje komende z linii polecen do zmennej
char *readLine(){
    fflush(stdout);
    char *SHstringCopy, *SHstring = NULL;
    size_t buffer = 0;
    printf("---->");
    getline(&SHstring, &buffer, stdin);
    return SHstring;
}