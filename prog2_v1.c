#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CMDMAXSIZE 50
#define PATHSIZE 60

int main(int argc, char const *argv[])
{
    char cmd[CMDMAXSIZE];
    int k;
    
    while (1) {

        printf("> ");
        scanf("%s", cmd);

        if (strcmp(cmd, "exit") == 0) {
            exit(0);
        }

        int ret = fork();

        if (ret < 0) {
            printf("Erro ao realizar fork.");
            exit(1);
        }

        if (ret == 0) {
            // child
            char cmd_path[PATHSIZE] = "/bin/";
            
            // concatenate two string to form command path
            strcat(cmd_path, cmd);

            int ret = execl(cmd_path, cmd, (char*)0);

            if (ret < 0) {
                exit(1);
            }

        } else {
            // father
            int status;
            // wait for child to finish and get status of process
            wait(&status);

            if (WEXITSTATUS(status) == 0) {
                printf("Executado com sucesso.\n");
            } else {
                printf("Código de retorno = %d.\n", WEXITSTATUS(status));
            }

        }

    }

    return 0;
}
