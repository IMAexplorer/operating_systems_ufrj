#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 1024

int main(void)
{
    int status, id, j;
    int pid = getpid();

    //pipe to send messages from parent to child
    int size_message_to_child;
    int pipe_parent_to_child[2];
    pipe(pipe_parent_to_child);

    //pipe to send messages from child to parent
    int size_message_to_parent;
    int pipe_child_to_parent[2];
    pipe(pipe_child_to_parent);

    char buffer[1025];

    printf("PID do Processo: %d \n", pid);

    int pid2 = fork();
    if (pid2 != 0) {
        //PARENT
        int pid_filho = pid2;
        printf("PARENT: pid: %d \n", getpid());
        
        char *message = "Luke, I am your father.";
        printf("PARENT: Sending Message: %s\n",message);
       
        //Using pipe to send the message
        write(pipe_parent_to_child[1], message, strlen(message));
        close(pipe_parent_to_child[1]);

        
        printf("PARENT: waiting message from child...\n");
        //wait for message from parent
        if ((size_message_to_parent = read ( pipe_child_to_parent[0], buffer, MSG_SIZE ) ) >= 0) {
            buffer[size_message_to_parent] = 0;  //terminate the string
            printf("PARENT: Received Message: %s \n",  buffer);
        }else{
            printf("PARENT: Error reading from pipe\n");
        }

        
        printf("PARENT: waiting child to end...\n");
        waitpid(pid_filho, &status, 0);

        printf("PARENT: Child ended. Ending parent too. \n");
        exit(0);

    } else {
        //CHILD
        int pid_filho = getpid();
        printf("CHILD: pid: %d \n",pid_filho);
        printf("CHILD: parent's pid: %d\n", pid);


        printf("CHILD: waiting message from parent...\n");
        //wait for message from parent
        if ((size_message_to_child = read ( pipe_parent_to_child[0], buffer, MSG_SIZE ) ) >= 0) {
            buffer[size_message_to_child] = 0;  //terminate the string
            printf("CHILD: Received Message: %s \n",  buffer);
        }else{
            printf("CHILD: Error reading from pipe\n");
        }

        char *message = "Noooooooooooooooooooooo";
        printf("CHILD: Sending Message: %s\n",message);
       
        //Using pipe to send the message
        write(pipe_child_to_parent[1], message, strlen(message));
        close(pipe_child_to_parent[1]);

        int j;
        for (j = 0; j <= 10000; j++);

        char str_j[20]; 
        sprintf(str_j, "%d", j);
       

        printf("CHILD: Sending new message: %s\n",str_j);
            
        //Using pipe to send the message
        write(pipe_child_to_parent[1], str_j, strlen(message));
        close(pipe_child_to_parent[1]);

        execl("/bin/ls", "ls", (char*)0);

    }
    exit(0);
}