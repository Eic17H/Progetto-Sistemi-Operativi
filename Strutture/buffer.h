#include <stdlib.h>
#include <stdbool.h>
#define DIM_BUFFER 5

// Tipo di dato che sarà nel buffer
    typedef struct{
    }Data;

// Tutto il necessario per il buffer
    typedef struct{
        Data* queue;
        bool* mutex;
        int* head;
        int* tail;
        int dim;
    }Buffer;

// Al thread si passano il buffer e dei dati predefiniti
    typedef struct{
        Buffer buffer;
        Data datiIniziali;
    }Pass;

// Crea e inizializza un buffer e ne restituisce l'indirizzo
    Buffer* initBuffer();

// Controllo disponibilità del buffer
    bool bufferPieno(Buffer buffer);
    bool bufferVuoto(Buffer buffer);

// Controllo zona critica
    void mutexLock(Buffer buffer);
    void mutexUnlock(Buffer buffer);

// Immissione ed estrazione dei dati
    void inserisciNelBuffer(Buffer buffer, Data in);
    Data estraiDalBuffer(Buffer buffer);
