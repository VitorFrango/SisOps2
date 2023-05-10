/*
**   UC:21111 - Sistemas Operativos
**    E-Folio B 2022-23 (mtts.c)
**
**    Aluno: 1802925 - Vitor Frango
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_LETRAS 26

pthread_mutex_t lock; // variável mutex para controlar acesso ao vetor de frequências

char *buf; // buffer para armazenar o conteúdo do arquivo

int buf_size; // tamanho do arquivo em bytes
int tam_bloco; // tamanho do bloco a ser processado por cada thread
int frequencias[NUM_LETRAS]; // vetor de frequências das letras do alfabeto


void *trabalhadora(void *arg) {
    int id = *((int *) arg);
    int i;

    int *contador_global = calloc(NUM_LETRAS, sizeof(int)); // vetor de contadores de letras
    if (contador_global == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    // processa ciclicamente os blocos de caracteres atribuídos à thread
    for (i = id * tam_bloco; i < buf_size; i += tam_bloco * NUM_LETRAS) {
        int fim_bloco = i + tam_bloco;
        if (fim_bloco > buf_size) {
            fim_bloco = buf_size;
            for (i = id * tam_bloco; i < (id + 1) * tam_bloco && i < buf_size; i++) {
                if (buf[i] >= 'A' && buf[i] <= 'Z') { // letra maiúscula
                    contador_global[buf[i] - 'A']++; // incrementa o contador global da letra
                } else if (buf[i] >= 'a' && buf[i] <= 'z') { // letra minúscula
                    contador_global[buf[i] - 'a']++;
                }
            }
        }
    }

    // imprime o resultado da tarefa
    printf("T%d= %7.3f%%\n", id, ((float) tam_bloco / buf_size) * 100);

    // adiciona o resultado da tarefa ao vetor de contadores global
    pthread_mutex_lock(&lock);
    for (i = 0; i < NUM_LETRAS; i++) {
        frequencias[i] += contador_global[i];
    }
    pthread_mutex_unlock(&lock);

    free(contador_global);

    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Escreva: %s <numero de tarefas trabalhadoras> <numero de caracteres por bloco> <ficheiro.txt>\n", argv[0]);
        printf("Número incorreto de argumentos.\n");
        return 1;
    }

    int i;
    int nt = atoi(argv[1]); // número de threads
    int nc = atoi(argv[2]); // tamanho do bloco em caracteres


    // teste se o numero de argumentos (tarefas "nt" ou caracteres "nc" é correto ambos >=1
    if (nt < 1 || nc < 1) {
        printf("Número de tarefas ou tamanho do bloco inválido. Tarefas e blocos de caracteres  >=1 \n");
        return 1;
    }


    int ids[nt]; // vetor de IDs das threads

    pthread_t threads[nt]; // vetor de threads

    FILE *f = fopen(argv[3], "rb"); // abre o arquivo para leitura em modo binário
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return 1;
    }

    fseek(f, 0, SEEK_END); // posiciona o cursor no fim do arquivo
    buf_size = ftell(f); // obtém o tamanho do arquivo em bytes
    fseek(f, 0, SEEK_SET); // reposiciona o cursor no início do arquivo

    buf = malloc(buf_size); // aloca memória para o buffer
    if (buf == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    if (fread(buf, 1, buf_size, f) != buf_size) { // lê o arquivo para o buffer
        printf("Erro ao ler o ficheiro.\n");
        return 1;
    }

    tam_bloco = (buf_size + nt + 1) / nt; // define o tamanho do bloco para cada thread


    printf("\n\nAnálise de letras do alfabeto com %d tarefas e blocos de %d caracteres\n", nt, nc);
    printf("\n\nFicheiro %s (%d bytes)\n", argv[3], buf_size);
    printf("\n\nRelatório de tarefas:\n");

    // Inicializa um objeto mutex chamado lock
    pthread_mutex_init(&lock, NULL);

    // Cria nt threads e as executa na função trabalhadora
    for (i = 0; i < nt; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, trabalhadora, &ids[i]);
    }

    // Aguarda cada thread terminar sua execução
    for (i = 0; i < nt; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nRelatório de caracteres:\n");

    for (i = 0; i < NUM_LETRAS; i++) {
        printf("%c =  %7.3f%%\n", 'A' + i, ((float) frequencias[i] / buf_size) * 100);
    }

    // Liberta a memória alocada dinamicamente para o buffer e fecha o arquivo
    free(buf);
    fclose(f);
    pthread_mutex_destroy(&lock);// Destrói o objeto mutex lock

    return 0;
}