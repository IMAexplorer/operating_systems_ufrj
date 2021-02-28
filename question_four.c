#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int ret;
    ret = fork();
    if (ret == 0) {
        int ret2 = execl("/bin/ll", "ll", (char*)0);
        printf("Return from exec %d.\n", ret2);
        printf("Por que este comando foi executado?\n");
    } else
        printf("Processo continua executando.\n");
}
