#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int ret1, ret2;
    ret1 = fork();
    ret2 = fork();
    printf("Programa em execução.\n");
    return 0;
}
