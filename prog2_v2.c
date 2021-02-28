#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CMDLINEMAXSIZE 200
#define CMDMAXSIZE 50

int main(int argc, char const *argv[])
{
    char command_line[CMDLINEMAXSIZE];
    char cmd[CMDMAXSIZE];
    int k;
    
    printf("> ");
    scanf("%s", command_line);

    k = 0;
    while (command_line[k] != ' ' || k < CMDMAXSIZE - 1) {
        cmd[k] = command_line[k];
        k++;
    }
    // add null character - cmd[49] = \0
    cmd[k+1] = '\0';

    int ret = fork();

    if (ret < 0) {
        printf("Erro ao realizar fork.");
        exit(1);
    }

    if (ret == 0) {
        // child

    } else {
        // father

    }

    return 0;
}
