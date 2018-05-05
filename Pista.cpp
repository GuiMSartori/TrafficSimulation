#include "Pista.h"
#include "LinkedQueue.cpp"
#include <cstdint>
#include <stdexcept>

Pista::Pista(double tamanhoMax, double velocidade, double t_ger_carro, double var_t) {
    this->tamanhoMax = tamanhoMax;
    this->velocidade = velocidade;
    this->t_ger_carro = t_ger_carro;
    this->var_t = var_t;
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

bool Pista::canFit(Carro carro) {
    if (carro.getTamanho() + 3 + tamanhoOcupado <= tamanhoMax) {
        return true;
    }
    return false;
}
