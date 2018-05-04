#include "Pista.h"
#include "LinkedQueue.cpp"
#include <cstdint>
#include <stdexcept>

Pista::Pista(float tamanhoMax, float velocidade) {
    this->tamanhoMax = tamanhoMax;
    this->velocidade = velocidade;
}

void Pista::enqueue(const Carro& data) {
    float tamanhoCarro = data.getTamanho();
    if (tamanhoCarro + 3 + tamanhoOcupado > tamanhoMax) {
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

float Pista::getVelocidade() {
    return velocidade;
}

float Pista::getTamanhoMax() {
    return tamanhoMax;
}

float Pista::getTamanhoOcupado() {
    return tamanhoOcupado;
}

float Pista::getEspacoLivre() {
    return tamanhoMax - tamanhoOcupado;
}
