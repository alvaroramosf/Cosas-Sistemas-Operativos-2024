//Ejercicio 20.
//Autor: Álvaro Ramos Fustero
//Fecha: 19/01/2024
// Programa: P1 | programa n F1 | P2.
//	Donde: P1, P2, y thead son programas, F1 es un fichero.
//	P2 recibe en su entrada estándar las n primeras lineas procedientes de la salida estandar de P1. n es un parámetro de programa, y si n = 0, 22 recibe en su entrada estandar la salida estándar de P1
// (es decir, que lo que tiene que hacer programa es:
// - sacar por salida estándar las n primeras líneas de P1 a P2 (si n != 0)
// - (si n = 0) copiar a F1 la salida estándar de P1
// - sacar por salida estándar a F1 la salida estándar de P1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>


int leerLinea(int fd, char* linea){
	char c;
	int i=0;
	int bytesLeidos = read(fd, &c, 1);
	while((bytesLeidos != 0) && (c!='\n')){
		linea[i]=c;
		i++;
		bytesLeidos = read(fd, &c, 1);
	}
	linea[i] = '\0';
	return i;
}

int main(int argc, char *argv[]){
	char buffer[1024];
	int n = atoi(argv[1]);
	int fd_fichero = open(argv[2], O_WRONLY | O_CREAT, 0777);//Abrimos fichero
	int caracteresLeidos, lineasLeidas=0;
	while((caracteresLeidos = leerLinea(0, buffer)) > 0){
		buffer[caracteresLeidos]='\n';
		write(fd_fichero, buffer, caracteresLeidos+1);//Escribinos en el fichero
		lineasLeidas ++;
		if(n==0 || (lineasLeidas<=n)){//Hay que enviar todo por salida estándar
			write(1, buffer, caracteresLeidos+1);
		}
	}
	close(fd_fichero);
	return 0;
}

