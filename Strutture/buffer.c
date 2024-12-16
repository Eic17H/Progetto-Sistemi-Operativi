#include "buffer.h"

Buffer* initBuffer(){
    // Alloca il buffer
        Buffer* buffer = (Buffer*) malloc(sizeof(Buffer));
        buffer->dim = DIM_BUFFER;
    // Alloca i campi
        buffer->queue = (Data*) malloc(sizeof(Data)*(buffer->dim));
        buffer->mutex = (bool*) malloc(sizeof(bool));
        buffer->head = (int*) malloc(sizeof(int));
        buffer->tail = (int*) malloc(sizeof(int));
    // Inizializza i campi
        *(buffer->mutex) = false;
        *(buffer->head) = 0;
        *(buffer->tail) = (-1)%(buffer->dim);
}

bool bufferPieno(Buffer buffer) {return 0== (*(buffer.tail) - *(buffer.head) +1) % buffer.dim;}

bool bufferVuoto(Buffer buffer) {return 0== (*(buffer.head) - *(buffer.tail) +1) % buffer.dim;}

void mutexLock(Buffer buffer) {*(buffer.mutex) = true;}

void mutexUnlock(Buffer buffer) {*(buffer.mutex) = false;}

void inserisciNelBuffer(Buffer buffer, Data in){
    while(bufferPieno(buffer) || *(buffer.mutex));
    mutexLock(buffer);
    buffer.queue[*(buffer.tail)] = in;
    *(buffer.tail) = (*(buffer.tail) + 1) % buffer.dim;
    mutexUnlock(buffer);
}

Data estraiDalBuffer(Buffer buffer){
    Data out;
    while(bufferVuoto(buffer) || *(buffer.mutex));
    mutexLock(buffer);
    out = buffer.queue[*(buffer.head)];
    *(buffer.head) = (*(buffer.head) + 1) % buffer.dim;
    mutexUnlock(buffer);
}