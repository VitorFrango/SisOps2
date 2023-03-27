//
// Created by Vitor Frango on 27/03/2023.
//
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("Eu sou o processo filho, \no meu PID é %d and my PPID é %d\n", getpid(), getppid());
    }
    else {
        printf("Eu sou o processo pai, o meu  PID é %d, \n criei um processo filho com o  PID %d\n", getpid(), pid);
    }

    return 0;
}