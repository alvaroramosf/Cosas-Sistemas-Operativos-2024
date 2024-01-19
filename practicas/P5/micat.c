#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	char *buffer[1000];
	if(argc == 1){//Si no tiene argumentos
		while(1){
			int NbytesLeidos = read(STDIN_FILENO, buffer, 1000);
			//printf ("Leidos %d bytes de la entrada estándar.\n", NbytesLeidos);
			write(STDOUT_FILENO, buffer, NbytesLeidos);
		}
	}
	else if (argc == 2){//Si le hemos pasado el nombre de un fichero destino
		//int fd = open(argv[1], O_WRONLY);
		int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		printf ("Fichero creado. Fd: %d \n", fd);
		int NbytesLeidos = read(STDIN_FILENO, buffer, 1000);
		printf ("Leidos %d bytes de la entrada estándar.\n", NbytesLeidos);
		write(fd, buffer, NbytesLeidos);
		
	}
	else printf("Error en el nº de argumentos. \nUso: micat [nombre fichero destino]. \n");
	
	return 0;
}

