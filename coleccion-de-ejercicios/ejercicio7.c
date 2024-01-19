//Ejercicio 7.
//Autor: Álvaro Ramos Fustero
//Fecha: 18/01/2024
//Programa redirecciona la salida estándar y de error del programa especificado en su segundo (y sucesivos) argumentos en el fichero especificado en el primero de ellos
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	int pid, fd_pipe[2], fd_salida, bytes;
	const int BUFSIZE = 512;
	pipe(fd_pipe);
	pid = fork();
	if(pid==0){//Hijo (ejecuta)
		close(fd_pipe[0]);//Cerramos el extremo de lectura de la tubería
		close(1);//Cerramos la entrada estándar
		dup(fd_pipe[1]);//Redirigimos la salida estandar a la tubería
		close(2);//Cerramos el error estándar
		dup(fd_pipe[1]);//Redirigimos el error estándar a la tubería
		execvp(argv[2], &argv[2]);//Ejecutamos el programa con los argumentos dados
		exit(0);
	}else{//Padre (redirecciona tubería a archivo)
		close(fd_pipe[1]);//Cerramos el extremo de escritura de la tubería
		fd_salida = open(argv[1], O_CREAT|O_WRONLY, 0777);
		char buffer[BUFSIZE];
		while((bytes = read(fd_pipe[0], &buffer, BUFSIZE)) > 0){
			write(fd_salida, &buffer, bytes);
		}
		exit(0);
	}
}
