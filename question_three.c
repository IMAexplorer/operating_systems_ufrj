#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int ret;
    ret = fork();
    if (ret == 0) {
        execl("/bin/ls", "ls", (char*)0);
        printf("Quando este comando será executado?\n");
    };
    printf("Por que a função printf anterior não foi executada?\n");
}
