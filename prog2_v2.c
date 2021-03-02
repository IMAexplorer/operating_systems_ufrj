#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CMDLINEMAXSIZE 200
#define CMDMAXSIZE 30
#define PATHSIZE 60
#define MAXPARAMSIZE 10

int main(int argc, char const *argv[])
{
    char cmd_line[CMDLINEMAXSIZE];
    int k, ret;

    while (1) {

        printf("> ");
        fgets(cmd_line, CMDLINEMAXSIZE, stdin);

         //removing \n from ending
         k = 0;
         while (cmd_line[k] != '\n')
            k++;

        cmd_line[k] = 0;

        // if exit, then stop
        if (strcmp(cmd_line, "exit") == 0) {
            exit(0);
        }

        // Split the strings
        int pos = 0, k = 0, j = 0;
        char ** params = malloc(MAXPARAMSIZE * sizeof(char*));
        params[0] = malloc(PATHSIZE * sizeof(char));

        for(int i = 0; i <= strlen(cmd_line) ; i++) {
            
            if (k == 9) // have to set NULL at the end
                break;

            if(cmd_line[i] == ' ' || cmd_line[i] == '\0') {
                params[k][j] = '\0';                
                k++;    //for next word
                j=0;    //for next word, init index to 0
                // allocate new space
                params[k] = malloc(PATHSIZE * sizeof(char));
            }
            else {            
                params[k][j] = cmd_line[i];
                j++;
            }
        }
        // add NULL to the end of array
        params[k] = '\0';

        char bin_path[30] = "/bin/";
        strcat(bin_path, params[0]);        

        // make fork
        ret = fork();
        if (ret  < 0) {
            printf("Erro ao realizar fork.");
            exit(1);
        }

        if (ret == 0) {
            
            int rt = execv(bin_path, params);

            printf("return %d\n", rt);

            if (rt < 0) {
                exit(1);
            }

        } else {
                    
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
