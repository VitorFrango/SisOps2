//
// Created by Vitor Frango on 27/03/2023.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork(); // cria uma cópia do processo pai

    if (pid == -1) {
        perror("fork"); // erro ao criar processo filho
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // processo filho
        printf("Eu sou o processo filho e tenho o PID=%5d\n", (int) getpid());
       // execlp("/bin/ls", "ls", "-la", NULL); // substitui a imagem do processo filho com o programa ls
        perror("exec"); // se o execlp() falhar, imprime o erro
        exit(EXIT_FAILURE);
    }
    else { // processo pai
        printf("Eu sou o processo pai e tenho o PID=%5d\n", (int) getpid());
        printf("O meu filho tem o PID=%5d\n", (int) getpid());
        printf("O meu filho tem o PPID=%5d\n", (int) getppid());
        exit(EXIT_SUCCESS);
    }

    return 0;
}
