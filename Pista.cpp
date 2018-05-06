#include "Pista.h"
#include "LinkedQueue.cpp"
#include <cstdint>
#include <stdexcept>
#include <time.h>
#include <stdlib.h>

Pista::Pista(double tamanhoMax, double velocidade, int t_ger_carro, int var_t) {
    this->tamanhoMax = tamanhoMax;
    this->velocidade = velocidade;
    this->t_ger_carro = t_ger_carro;
    this->var_t = var_t;
    this->entradas = NULL;
}

Pista::~Pista() {
    delete entradas;
    clear();
}

void Pista::enqueue(const Carro& data) {
    double tamanhoCarro = data.getTamanho();
    if (!canFit(data)) {
        throw std::out_of_range("Pista Enqueue");
    }
    tamanhoOcupado += tamanhoCarro + 3;
    LinkedQueue::enqueue(data);
}

Carro Pista::dequeue() {
    if (empty()) {
        throw std::out_of_range("");
    }
    tamanhoOcupado -= (front().getTamanho() + 3);
    return LinkedQueue::dequeue();
}

double Pista::getVelocidade() {
    return velocidade;
}

double Pista::getTamanhoMax() {
    return tamanhoMax;
}

double Pista::getTamanhoOcupado() {
    return tamanhoOcupado;
}

double Pista::getEspacoLivre() {
    return tamanhoMax - tamanhoOcupado;
}

int Pista::getTempoGeracao() {
    srand(time(NULL));
    int var = rand() % (var_t * 2);
    int tempo = t_ger_carro - var_t + var;
    return tempo;
}


bool Pista::canFit(Carro carro) {
    if (carro.getTamanho() + 3 + tamanhoOcupado <= tamanhoMax) {
        return true;
    }
    return false;
}

structures::ArrayList<Pista *> * Pista::getEntradas() {
    return entradas;
}

void Pista::setEntradas(structures::ArrayList<Pista*> * entradas) {
    this->entradas = entradas;
}