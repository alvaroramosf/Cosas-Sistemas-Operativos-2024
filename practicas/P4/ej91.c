#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
void captura(){
;
}
void duerme(int segundos){
	alarm(segundos);
	signal(SIGALRM, captura  );//Captura SIGALRM
	pause();
}


int main(int argc, char *argv[]){
	int y, x;
	x=atoi(argv[1]);
	y=atoi(argv[2]);
	int pid = fork();
	if(pid==0){//Proceso hijo
		signal(SIGTSTP, SIG_DFL);
		signal(SIGCONT, SIG_DFL);
		while(1){
			duerme(x);
			printf("Hijo: envio un mensaje...\n");
		}
	}
	else{//Proceso padre
		duerme(y);
		printf("Padre: suspendo ejecucion hijo...\n");
		kill(pid,SIGTSTP);//Suspender ejecucion hijo SIGSTP
		duerme(y);
		printf("Padre: retomo ejecucion hijo...\n");
		kill(pid,SIGCONT);//Retomar ejecucion hijo SIGCONT
		duerme(y);
		printf("Padre: mato a mi hijo...\n");
		kill(pid,SIGKILL);
		//Matar hijo KILL
	}
	return 0;
}

