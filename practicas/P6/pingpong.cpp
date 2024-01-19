#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "error.h"
#include <time.h>

const int MAX_PELOTAS=99;

//Para meter dos pelotas mandar siguser los dos procesos y que ambos incrementen su contador num
//num pelotas, y que lleven la cuenta de en que pelota están

void delay(int number_of_seconds)//Robada de internet
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;
	// Storing start time
	clock_t start_time = clock();
	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds);
}

//LLeva la lógica del contador de pelotas
void sigPelota(int &pelotaActual, int numPelotas){
	pelotaActual++;
	if(pelotaActual >= NUM_PELOTAS){
		pelotaActual=0;
	}
}

int main(){
	int ppadrehijo[2]; int phijopadre[2];//Tuberías
	pipe(ppadrehijo);
	pipe(phijopadre);
	int pelota=0; int n=1; int numPelotas=0; int pelotaActual =0;
	int *punteropelota;
	punteropelota=&pelota;
	switch(fork()){
		case -1: 
			printf("Error en el fork \n");
		case 0: //Proceso hijo
			printf("Soy el proceso hijo \n");
			while(pelota<MAX_PELOTAS && n!=0){
				n=read(ppadrehijo[0], punteropelota, sizeof(int));//Recibe pelota
				delay(1000);//Espera un segundo
				pelota++;
				printf("pelota %d  hace pong %d \n",pelotaActual, pelota);
				sigPelota(pelotaActual, numPelotas);
				write(phijopadre[1], punteropelota, sizeof(int));//Envía pelota
				}
				exit(0);			
		default://Proceso padre
			printf("Soy el proceso padre \n");
			write(ppadrehijo[1], punteropelota, sizeof(int));//Mandar la pelota una primera vez
			while(pelota<MAX_PELOTAS && n!=0){
				n=read(phijopadre[0], punteropelota, sizeof(int));//Recibe pelota
				delay(1000);//Espera un segundo
				pelota++;
				printf("pelota %d  hace ping %d \n",pelotaActual, pelota);
				sigPelota(pelotaActual, numPelotas);
				write(ppadrehijo[1], punteropelota, sizeof(int));//Envía pelota
				}
			exit(0);
	}
	return(-1);
}
	
