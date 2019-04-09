#include <sdtio.h>
#include "readLineShell"

void shellCycle(){
    char *line;
    line = readLine();
    free(line);
}


int main(){
    char *line;
    line = readLine();
    return EXIT_CODE;
}