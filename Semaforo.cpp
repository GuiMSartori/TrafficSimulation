#include <time.h>
#include <stdlib.h>
#include "Semaforo.h"

Semaforo::Semaforo(structures::ArrayList<Pista *> saida, structures::ArrayList<Pista *> entrada, structures::ArrayList<double> probabilidades) {
    this->saida = saida;
    this->entrada = entrada;
    this->probabilidades = probabilidades;
}

void Semaforo::mudaSinal() {
    if (aberto) {
        aberto = false;
    } else {
        aberto = true;
    }
}

void Semaforo::trocaDePista(Pista * pista) {
    int index = 0;
    for (int i = 0; i < saida.size(); i++) {
        if (saida[i] == pista) {
            index = i;
            break;
        }
    }
    srand(time(NULL));
    int evento = rand() % 100;
    if (0 <= evento && evento < probabilidades[0]) {
        if (entrada[0]->canFit(saida[index]->front())) {
            entrada[0]->enqueue(saida[index]->dequeue());
        }
    } else if (probabilidades[0] <= evento && evento < probabilidades[1]) {
        if (entrada[1]->canFit(saida[index]->front())) {
            entrada[1]->enqueue(saida[index]->dequeue());
        }
    } else {
        if (entrada[2]->canFit(saida[index]->front())) {
            entrada[2]->enqueue(saida[index]->dequeue());
        }
    }
}

bool Semaforo::isAberto() {
    return aberto;
}
