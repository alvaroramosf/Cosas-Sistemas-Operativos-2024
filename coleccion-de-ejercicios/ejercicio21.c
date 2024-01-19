//Ejercicio 21
//Autor: Álvaro Ramos Fustero
//Fecha: 19/01/2024
// Programa: ./ejercicio F1
//		./ejercicio F3 < F1 > F2
//		./ejercicio
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE];
	int bytes;
	if(argc==1){//Error, faltan parámetros.
		perror("ERROR: Faltan parámetros.\n");
		exit(2);
	}else if(argc ==2){//Redirige entrada estandar a salida estándar y a F1
		int fd_F1 = open(argv[1], O_WRONLY | O_CREAT, 0777);//Abrimos fichero
		while((bytes = read(0, &buffer, BUFSIZE)) > 0){
			write(1, &buffer, bytes);
			write(fd_F1, &buffer, bytes);
		}
		close(fd_F1);
	}else if(argc ==6){
		int fd_F3 = open(argv[1], O_WRONLY | O_CREAT, 0777);//Abrimos fichero F3, escritura
		int fd_F1 = open(argv[3], O_RDONLY);//Abrimos fichero F1, lectura
		int fd_F2 = open(argv[5], O_WRONLY | O_CREAT, 0777);//Abrimos fichero F2, escritura
		while((bytes = read(fd_F1, &buffer, BUFSIZE)) > 0){
			write(fd_F2, &buffer, bytes);
			write(fd_F3, &buffer, bytes);
		}
		close(fd_F1);
		close(fd_F2);
	}else{
		perror("ERROR: Número de parámetros incorrecto.\n");
		exit(2);;
	}
	return 0;
}


