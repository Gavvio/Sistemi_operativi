#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char** argv) {
    int maggiore=0;
    int maggiore_pid=0;
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
                    printf("errore in fork \n");
                }else if(pid == 0){
                    //figlio
                    printf("ciao sono il figlio \n");
                    srand(getpid());
                    int r=rand()%256;
                    printf("Numero randomico: %d (PID: %d)\n",r,getpid());
                    exit(r);
                }else{
                    //padre
                    printf("ciao sono il padre \n");
                    int status;
                    waitpid(pid,&status,0);
                    if(WIFEXITED(status)){
                        int a=WEXITSTATUS(status);
                        printf("aspettato il figlio con PID: %d che ha ritornato: %d \n", pid,a);
                        if(a>maggiore){
                            maggiore=a;
                            maggiore_pid=pid;
                            printf("ho un nuovo numero maggiore \n");
                        }
                    }
                }
            }
        }
    }
    printf("il numero maggiore finale ottenuto dal figlio con PID: %d è: %d \n",maggiore_pid,maggiore);
    return 0;
}
