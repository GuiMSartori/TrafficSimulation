#include <time.h>
#include <stdlib.h>
#include "Semaforo.h"

Semaforo::Semaforo(structures::ArrayList<Pista *> saida, structures::ArrayList<structures::ArrayList<double>> probabilidades) {
    this->saida = saida;
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
        if (i == saida.size() - 1) {
            throw std::exception();
        } 
    }
    srand(time(NULL));
    int evento = rand() % 100;
    if (0 <= evento && evento < probabilidades[index][0]) {
        if (saida[index]->getEntradas()[0]->canFit(saida[index]->front())) {
            saida[index]->getEntradas()[0]->enqueue(saida[index]->dequeue());
        }
    } else if (probabilidades[index][0] <= evento && evento < probabilidades[index][1]) {
        if (saida[index]->getEntradas()[1]->canFit(saida[index]->front())) {
            saida[index]->getEntradas()[1]->enqueue(saida[index]->dequeue());
        }
    } else {
        if (saida[index]->getEntradas()[2]->canFit(saida[index]->front())) {
            saida[index]->getEntradas()[2]->enqueue(saida[index]->dequeue());
        }
    }
}

bool Semaforo::isAberto() {
    return aberto;
}
