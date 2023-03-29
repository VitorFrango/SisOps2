//
// Created by Vitor Frango on 29/03/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n;
    pid_t pid_B, pid_C, pid_D;

    // Verifica se o número de argumentos é correto
    if (argc != 2) {
        printf("Uso: ./gsn n\n");
        exit(1);
    }

    // Converte o argumento para inteiro
    n = atoi(argv[1]);

    // Verifica se n é positivo
    if (n <= 0) {
        printf("n deve ser maior que zero.\n");
        exit(1);
    }

    // Passo A
    pid_B = fork();
    if (pid_B == 0) {
        // Passo B
        execl("/bin/head", "head", "/dev/urandom", "-c", argv[1], NULL);
    } else {
        wait(NULL);
        pid_C = fork();
        if (pid_C == 0) {
            // Passo C
            execl("/bin/hexdump", "hexdump", "-e", "'1/4 \"%d \"'", NULL);
        } else {
            wait(NULL);
            pid_D = fork();
            if (pid_D == 0) {
                // Passo D
                execl("/bin/sort", "sort", NULL);
            } else {
                wait(NULL);
                printf("\n");
            }
        }
    }

    return 0;
}
