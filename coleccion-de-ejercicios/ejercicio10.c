//Ejercicio 10.
//Autor: Álvaro Ramos Fustero
//Fecha: 18/01/2024
//Programa que muestra por la salida estándar el nº total de ficheros en el directorio, y su tamaño total.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char *argv[]){
	int pid, fd_pipe[2];
	pipe(fd_pipe);
	pid = fork();//Creamos un hijo que ejecute el comando
	if(pid==0){//Hijo
		close(fd_pipe[0]);//Cerramos el extremo de lectura de la pipe
		close(1);//Cerremos la salida estandar del proceso
		dup(fd_pipe[1]);//Redirigimos la salida estándar al extremo de la tubería.
		execlp("ls","ls","-l",0);//Ejecutamos ls 
		exit(0);
	}else{//Padre
		const int BUFFER_SIZE= 1024;
		char buffer[BUFFER_SIZE], *v[8], *token;;
		int numeroFicheros = 0, tamagno = 0;
		close(fd_pipe[1]);//Cerramos el extremo de escritura de la pipe
		close(0);//Redirigimos la entrada estándar al extremo de lectura de la tubería
		dup(fd_pipe[0]);
		//fgets(buffer, BUFFER_SIZE, stdin);
		while(fgets(buffer, BUFFER_SIZE, stdin) != NULL){//Leemos línea a línea
			if(buffer[0]=='d'){//Es directorio
				;
			}else if(buffer[0]=='-'){//No es un directorio
				printf("Leido no directorio. \n");
				token = strtok(buffer, " ");
				int i = 0;
				while(token != NULL && i < 5){
					if (i == 4) {
						tamagno += atoi(token);
					}
					token = strtok(NULL, " ");
					i++;
				}
				numeroFicheros++;
			}
			else{
				printf("Error de lectura. \n");
			}
		}
		printf("Hay %d ficheros que no son directorios, que ocupan un total de %d bytes.\n", numeroFicheros, tamagno);
	}
}
