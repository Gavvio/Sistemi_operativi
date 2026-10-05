#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
static int is_prime(long x){
	if(x<2)return 0;
	if(x==2)return 1;
	if(x%2==0) return 0;
	for(long d=3;d*d<=x;d+=2){
		if(x%d==0) return 0;
	}
	return 1;
}
int main(int argc, char** argv) {
	int totale_primi=0;
	if (argc < 2) {
		printf("parametri passati sbagliati \n");
		return 1;
	}
	else {
		for(int i=1;i<argc;i++){
			long num = atol(argv[i]);
			if (num < 0) {
				printf("parametri passati sbagliati \n");
				return 1;
			}else{
				pid_t pid;
				pid=fork();
				if(pid<0){
					//errore
					printf("errore in fork \n");
				}else if(pid == 0){
					//figlio
					int r=is_prime(num);
					if(r==1){
					printf("Numero inserito: %ld (Primo)\n",num);
					}
					exit(r);
				}else{
					//padre
					int status;
					waitpid(pid,&status,0);
					if(WIFEXITED(status)){
						int a=WEXITSTATUS(status);
						if(a==1){
							totale_primi++;
						}
					}
				}
			}
		}
	}
	printf("il numero finale di primi ottenuto è: %d\n",totale_primi);
	return 0;
}
