//Ejercicio 30
//Autor: Álvaro Ramos Fustero
//Fecha: 19/01/2024
//Cronómetro	Iniciar/Parar: ^C
//		Salir: ^Y

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

int contando = 0;

struct timeval inicio, fin;


///int gettimeofday(struct timeval *ts, NULL);

void handler_SIGINT(int signum){
	signal(SIGINT, handler_SIGINT);//Nos protegemos otra vez contra SIGINT
	if(contando == 0){
		gettimeofday(&inicio, NULL);
		contando = 1;
	}
	else{
		gettimeofday(&fin, NULL);
		contando = 0;
		long seconds = fin.tv_sec - inicio.tv_sec;
		long micros = fin.tv_usec - inicio.tv_usec;
		if (micros < 0) {
			seconds--;
			micros += 1000000;
		}
		printf("Han pasado %ld segundos y %ld microsegundos\n", seconds, micros);

		
	}		
}

void handler_SIGALRM(int signum){
	printf("Han pasado 60 segundos. El programa va a finalizar. \n");//No nos protejemos, total vamos a acabar
	exit(0);
}

void handler_SIGQUIT(int signum){//No nos protejemos, total vamos a acabar
	printf("Se ha pulsado ^Y. El programa va a finalizar. \n");
	exit(0);
}


int main() {
    alarm(60);//Establecer una alarma para que genere SIGALRM después de 60 segundos.
    signal(SIGALRM, handler_SIGALRM);//Nos protegemos contra SIGALRM
    signal(SIGINT, handler_SIGINT);//Nos protegemos contra SIGINT
    signal(SIGQUIT, handler_SIGQUIT);//Nos protegemos contra SIGQUIT
    while(1){
    ;
    }
    exit(0);
}
