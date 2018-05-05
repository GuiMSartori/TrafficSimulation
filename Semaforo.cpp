#include <time.h>
#include <stdlib.h>
#include "Semaforo.h"

Semaforo::Semaforo(Pista * saida, structures::ArrayList<Pista *> entrada, structures::ArrayList<float> probabilidades) {
    this->saida = saida;
    this->entrada = entrada;
    this->probabilidades = probabilidades;
}

Semaforo::~Semaforo() {
    delete saida;
}
    
void Semaforo::mudaSinal() {
    if (aberto) {
        aberto = false;
    } else {
        aberto = true;
    }
}
    
void Semaforo::trocaDePista() {
    srand(time(NULL));
    int evento = rand() % 100;
    if (0 <= evento && evento < probabilidades[0]) {
        if (entrada[0]->canFit(saida->front())) {
            entrada[0]->enqueue(saida->dequeue());
        }
    } else if (probabilidades[0] <= evento && evento < probabilidades[1]) {
        if (entrada[1]->canFit(saida->front())) {
            entrada[1]->enqueue(saida->dequeue());
        }
    } else {
        if (entrada[2]->canFit(saida->front())) {
            entrada[2]->enqueue(saida->dequeue());
        }
    }
}
    
bool Semaforo::isAberto() {
    return aberto;
}
    