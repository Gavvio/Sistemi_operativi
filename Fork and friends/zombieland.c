#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
int main(int argc, char** argv) {
	if (argc > 2 || argc == 1) {
		printf("numero parametri passati sbagliato \n");
		return 1;
	}
	else {
		printf("parametri giusti \n");
		errno = 0;
		char* endptr;
		int num = strtol(argv[1], &endptr, 10);
		if (errno != 0 || *endptr != '\0' || num < 0) {
			printf("input sbagliato \n");
			return 1;
		}
		else {
			printf("input giusto \n");
			for (int i = 0; i < num; i++) {
				pid_t pid;
				pid = fork();
				if (pid < 0) {
					//errore
					printf("errore in fork \n");
				}
				else if (pid == 0) {
					//figlio
					printf("Sono il processo: %d, figlio di: %d \n", getpid(), getppid());
				}
				else {
					//padre
					sleep(30);
					wait(NULL);
					printf("processo padre termina aspettando e dormendo \n");
				}
			}
		}
	}
}