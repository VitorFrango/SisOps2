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
        printf("Parent process PID=%5d\n", #include <stdio.h>
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

        printf("Parent process PPID=%5d\n", (int) getppid());

    } else {
        // fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}