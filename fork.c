//
// Created by Vitor Frango on 25/03/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // child process
        printf("Child process PID=%5d\n", (int) getpid());
        printf("Child process PPID=%5d\n", (int) getppid());

    } else if (pid > 0) {
        // parent process
        printf("Parent process PID=%5d\n", (int) getpid());
        printf("Parent process PPID=%5d\n", (int) getppid());

    } else {
        // fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}