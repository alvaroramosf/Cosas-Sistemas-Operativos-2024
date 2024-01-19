#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 4 || strcmp(argv[argc-2], "+") != 0) {
        fprintf(stderr, "Uso: %s <app1> <arg1> ... + <app2> <arg1> ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Encontrar el índice del símbolo '+'
    int plus_index;
    for (plus_index = 1; plus_index < argc; ++plus_index) {
        if (strcmp(argv[plus_index], "+") == 0) {
            break;
        }
    }

    // Verificar si se proporcionaron aplicaciones a ejecutar
    if (plus_index == 1 || plus_index == argc - 1) {
        fprintf(stderr, "Error: Se deben proporcionar aplicaciones para ejecutar en paralelo.\n");
        exit(EXIT_FAILURE);
    }

    // Configurar los argumentos para cada aplicación
    argv[plus_index] = NULL;  // Establecer NULL para señalar el final de la lista de argumentos de la primera aplicación

    // Crear un proceso hijo para ejecutar la primera aplicación
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Error al crear el proceso hijo");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Código ejecutado por el hijo
        execvp(argv[1], &argv[1]);
        perror("Error al ejecutar la primera aplicación");
        exit(EXIT_FAILURE);
    } else {
        // Código ejecutado por el padre
        // Esperar a que el primer hijo termine
        waitpid(child_pid, NULL, 0);

        // Ejecutar la segunda aplicación en el proceso padre
        execvp(argv[plus_index + 1], &argv[plus_index + 1]);
        perror("Error al ejecutar la segunda aplicación");
        exit(EXIT_FAILURE);
    }

    return 0;
}

