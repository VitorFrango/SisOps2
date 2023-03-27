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
        printf("Eu sou o processo filho!\n");
        execlp("/bin/ls", "ls", "-la", NULL); // substitui a imagem do processo filho com o programa ls
        perror("exec"); // se o execlp() falhar, imprime o erro
        exit(EXIT_FAILURE);
    }
    else { // processo pai
        printf("Eu sou o processo pai, meu filho tem o PID %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
