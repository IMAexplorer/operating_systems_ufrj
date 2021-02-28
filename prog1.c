#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MSGSIZE 25

int main(int argc, char const *argv[])
{
    
    int status, id, j, child_pid;
    int pipefd_father[2], pipefd_son[2];

    printf("O PID do processo é %d", getpid());

    // initilialize pipes
    if (pipe(pipefd_father) < 0 || pipe(pipefd_son) < 0) {
        printf("Erro com pipe.\n");
        exit(1);
    }

    // Forks
    int ret_pid = fork();
    if (ret_pid < 0) {
        printf("Erro ao criar processo.\n");
        exit(1);
    }
    // Apenas o pai irá executar porque fork irá retornar 0 para o filho
    if (ret_pid) {
        
        char father_buf[MSGSIZE];
        int rcv_j;
        
        close(pipefd_father[0]);    // close read
        close(pipefd_son[1]);
        // Mostre na console o PID do processo pai e do processo filho
        printf("PARENT: O PID do processo pai é %d e o PID do filho é %d.\n", id, child_pid);

        // Monte uma mensagem e a envie para o processo filho
        char* msg_father = "Luke, I am your father.\n";
        
        write(pipefd_father[1], msg_father, MSGSIZE);
        close(pipefd_father[1]);    // close write

        // Mostre na tela o texto da mensagem envi/ada
        printf("PARENT: %s", msg_father);

        // Aguarde a resposta do processo filho        
        // Mostre na tela o texto recebido do processo filho
        read(pipefd_son[0], father_buf, MSGSIZE);

        printf("PARENT: %s", father_buf);

        // Aguarde mensagem do filho e mostre o texto recebido
        read(pipefd_son[0], &rcv_j, sizeof(j));

        printf("PARENT: O Valor de j é %d", rcv_j);
        // Aguarde o término do processo filho
        wait(NULL);        
        // Informe na tela que o filho terminou e que o processo pai também vai encerrar
        printf("O processo pai finalizou e o processo filho irá finalizar também.\n");
    } else {
        // apenas o filho irá executar esse trecho devido ao retorno de de fork()        
        char buf[MSGSIZE];
        int father_pid = getppid();
        
        close(pipefd_father[1]);
        close(pipefd_son[0]);

        // Mostre na tela o PID do processo corrente e do processo pai
        printf("CHILD: O PID do processo atual é %d e do processo pai é %d\n", getpid(), father_pid);

        // Aguarde a mensagem do processo pai e ao receber mostre o texto na tela
        
        read(pipefd_father[0], buf, MSGSIZE);

        printf("CHILD: %s", buf);

        // Envie uma mensagem resposta ao pai
        char *son_msg = "Noooooooooooooooooooooo\n";
        
        write(pipefd_son[1], son_msg, MSGSIZE);

        for (j = 0; j < 10000; j++);

        // Envie mensagem ao processo pai com o valor final de “j”
        write(pipefd_son[1], &j, sizeof(j));

        // Execute o comando abaixo e responda às perguntas

        execl("/bin/ls", "ls", (char*)0);
    }
    exit(0);
}
