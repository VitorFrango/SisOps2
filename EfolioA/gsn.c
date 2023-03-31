//
// Created by Vitor Frango on 29/03/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid1, pid2, pid3;

    // Verifica se o número de argumentos é correto
    if (argc != 2) {
        printf("Número incorreto de argumentos. Use: %s <n>\n", argv[0]);
        exit(1);
    }

    // Converte o argumento para um número inteiro
    int n = atoi(argv[1]);

    // Verifica se o valor de n é válido
    if (n <= 0) {
        printf("O valor de n deve ser positivo.\n");
        exit(1);
    }

    // Passo 1: head -c NNN /dev/urandom >tmp.bin
    printf("Processo A: PID=%d PPID=%d\n", getpid(), getppid());
    fflush(stdout);
    if ((pid1 = fork()) == 0) {
        freopen("tmp.bin", "w", stdout);
        execl("/usr/bin/head", "head", "-c", argv[1], "/dev/urandom", NULL);
    } else {
        waitpid(pid1, NULL, 0);
    }

    // Passo 2: hexdump -v -e "/1 \"%d\\n\"" <tmp.bin >tmp.txt
    printf("Processo B: PID=%d PPID=%d\n", getpid(), getppid());
    fflush(stdout);
    if ((pid2 = fork()) == 0) {
        freopen("tmp.txt", "w", stdout);
        execl("/usr/bin/hexdump", "hexdump", "-v", "-e", "/1 \"%d\\n\"", "<", "tmp.bin", NULL);
    } else {
        waitpid(pid2, NULL, 0);
    }

    // Passo 3: sort -g tmp.txt
    printf("Processo C: PID=%d PPID=%d\n", getpid(), getppid());
    fflush(stdout);
    if ((pid3 = fork()) == 0) {
        execl("/usr/bin/sort", "sort", "-g", "tmp.txt", NULL);
    } else {
        waitpid(pid3, NULL, 0);
    }

    // Imprime a lista ordenada em decimal na saída padrão
    printf("Processo A: Lista ordenada em decimal:\n");
    fflush(stdout);
    freopen("tmp.txt", "r", stdin);
    int num;
    while (scanf("%d", &num) == 1) {
        printf("%d\n", num);
    }

    return 0;

}
