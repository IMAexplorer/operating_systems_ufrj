#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int ret;
    ret = fork();
    if (ret == 0)
        execl("/bin/ls","ls", (char*)0);
    else
        printf("Processo continua executando.\n");
    return 0;
}
