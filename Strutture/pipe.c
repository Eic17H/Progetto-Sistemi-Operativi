#include "pipe.h"

// Usa dati nel padre
void use(Data* data, int lung){
    for(int i=0; i<lung-1; i++) printf("%d ", data[i]);
    printf("%d\n", data[lung-1]);
}

// Genera dati nel figlio
void gen(Data* data, int lung){
    for(int i=0; i<lung; i++) data[i] = rand()%10;
}

int main(){
    int pipe_fds[2];
    Data through[LUNG];

    // Se non riesce a fare la pipeS
    if(pipe(pipe_fds) == -1) {
        perror("Pipe call");
        exit(1);
    }

    pid_t pid;
    pid=fork();

    // Se non riesce a fare la fork
    if(pid < 0) {perror("fork call"); _exit(2);}

    else if(pid==0){
        // Figlio: genera dati e li mette nella pipe
        while(1){
            gen(through, LUNG);
            close(pipe_fds[0]);
            write(pipe_fds[1], through, LUNG*sizeof(Data));
        }
    }else{
        // Padre: legge dati dalla pipe e li usa
        while(1){
            close(pipe_fds[1]);
            read(pipe_fds[0], through, LUNG*sizeof(Data));
            use(through, LUNG);
        }
    }
}