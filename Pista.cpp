#include "Pista.h"
#include "LinkedQueue.cpp"
#include <cstdint>
#include <stdexcept>

Pista::Pista(float tamanhoMax, float velocidade, structures::ArrayList<Pista *> saida) {
    this->tamanhoMax = tamanhoMax;
    this->velocidade = velocidade;
    this->saida = saida;
}

void Pista::enqueue(const Carro& data) {
    float tamanhoCarro = data.getTamanho();
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

bool Pista::canFit(Carro carro) {
    if (carro.getTamanho() + 3 + tamanhoOcupado <= tamanhoMax) {
        return true;
    }
    return false;
}
