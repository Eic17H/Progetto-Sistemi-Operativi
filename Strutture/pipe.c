#include "pipe.h"

void use(Data* data, int lung){
    for(int i=0; i<lung-1; i++) printf("%d ", data[i]);
    printf("%d\n", data[lung-1]);
}

void gen(Data* data, int lung){
    for(int i=0; i<lung; i++) data[i] = rand()%10;
}

int main(){
    int pipe_fds[2];
    Data through[LUNG];

    if(pipe(pipe_fds) == -1) {
        perror("Pipe call");
        exit(1);
    }

    pid_t pid;
    pid=fork();
    if(pid < 0) {perror("fork call"); _exit(2);}
    else if(pid!=0) while(1){
        // Padre: gestione generale
        while(1){
            close(pipe_fds[1]);
            read(pipe_fds[0], through, LUNG*sizeof(Data));
            use(through, LUNG);
        }
    }else{
        // Figlio: guardia
        while(1){
            gen(through, LUNG);
            close(pipe_fds[0]);
            write(pipe_fds[1], through, LUNG*sizeof(Data));
        }
    }
}