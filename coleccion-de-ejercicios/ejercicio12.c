//Ejercicio 12.
//Autor: Álvaro Ramos Fustero
//Fecha: 18/01/2024
//Programa contiene la funcion ejecutar, que ejecuta el programa dado en el argumento de forma asíncrona (si byte es 0) o síncrona (si el byte es 1)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>



int ejecutar(char comando[1000], bool byte){
	int pid = fork();
	if(pid == 0){//Hijo
		char *vector[100];
		vector[0] = strtok(comando, " ");
		int i = 0;
		while(vector[i] != NULL){
			i++;
			vector[i]=strtok(NULL, " ");
		}
		execvp(vector[0], &vector[0]);
		exit(0);
	}else{//Padre
		if(byte){//Si asíncrona esperamos a que termine para devolver el control
			wait(NULL); //Esperamos a que el comando termine, si ejecución síncrona
		}
		else{
			;//No esperamos nada.
		}
		return pid;
	}
}

int main(){
	char comando[1000]= "ls -l";
	int pid_hijo=ejecutar(comando, false);
	printf("El pid del proceso encargado de ejecutar el comando es %d.\n", pid_hijo);
	exit(0);
	return 0;
}
