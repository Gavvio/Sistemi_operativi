#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char** argv) {
    if (argc > 2 || argc == 1) {
        printf("parametri passati sbagliati \n");
        return 1;
    }
    else {
        errno = 0;
        char* endptr;
        int num = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || num < 0) {
            return 1;
        }else{
            printf("input giusto, iniziamo \n");
            for(int i=0;i<num;i++){
                pid_t pid;
                pid=fork();
                if(pid<0){
                    //errore
                    printf("errore in fork");
                }else if(pid == 0){
                    //figlio
                    printf("ciao sono il figlio");
		    exit(3);
                }else{
                    //padre
                    printf("ciao sono il padre");
		    int status;
		    wait(&status);
		    if(WIFEXITED(status)){
		    int a=WEXITSTATUS(status);
		    printf("aspettato il figlio che ha ritornato: %d",a);
		    }
                }
            }
        }
    }
    return 0;
}