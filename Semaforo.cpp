#include <time.h>
#include <stdlib.h>
#include "Semaforo.h"

Semaforo::Semaforo(structures::ArrayList<Pista *> saida, structures::ArrayList<double> * probabilidades) {
    this->saida = saida;
    this->probabilidades = probabilidades;
    for (int i = 0; i < 4; i++) {
        this->sinal[i] = false;
    }
    index_aberto = 0;
}

Semaforo::~Semaforo() {
    delete[] probabilidades;
}

void Semaforo::mudaSinal() {
    for (auto i = 0; i < 4; i++) {
        if (sinal[i] == true) {
            sinal[i] = false;
            return;
        }
    }
    if (index_aberto >= 3) {
        index_aberto = 0;
    } else {
        index_aberto++;
    }
    sinal[index_aberto] = true;
    return;
}

void Semaforo::trocaDePista(int index, int destino) {
    if (saida[index]->getEntradas()->at(destino)->canFit(saida[index]->front())) {
        saida[index]->getEntradas()->at(destino)->enqueue(saida[index]->dequeue());
    } else {
        throw std::out_of_range("trocaDePista");
    }
}

int Semaforo::gerarDestino(int index) {
    srand(time(NULL));
    int evento = rand() % 100;
    if (0 <= evento && evento < probabilidades[index][0]) {
        return 0;
    } else if (probabilidades[index][0] <= evento && evento < probabilidades[index][1]) {
        return 1;
    } else {
        return 2;
    }
}

bool Semaforo::isAberto(int index) {
    return sinal[index];
}

Pista * Semaforo::getSaida(int index) {
    return saida.at(index);
}

int Semaforo::getPistaAberta() {
    return index_aberto;
}
