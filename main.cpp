#include <cstdlib>
#include "linked_list.h"
#include "LinkedQueue.h"
#include "Evento.h"
#include "Semaforo.h"

structures::LinkedList<Evento> relogio;
structures::LinkedList<Pista> pistas;
structures::LinkedList<Semaforo> semaforos;

int tempo_total;
int tempo_simulado;

void init();

int main(int argc, char** argv) {
    init();
    return 0;
}

void init() {
    
}