#include "Pista.h"
#include "LinkedQueue.cpp"
#include <cstdint>
#include <stdexcept>
#include <time.h>
#include <stdlib.h>

Pista::Pista(double tamanhoMax, double velocidade, int t_ger_carro, int t_var) {
    this->tamanhoMax = tamanhoMax;
    this->velocidade = velocidade;
    this->t_ger_carro = t_ger_carro;
    this->t_var = t_var;
    this->entradas = new Pista *[3];
}

Pista::~Pista() {
    if(entradas != nullptr) {
        delete[] entradas;
    }
    clear();
}

void Pista::enqueue(const Carro& data) {
    double tamanhoCarro = data.getTamanho();
    if (!canFit(data)) {
        throw std::out_of_range("Pista Enqueue");
    }
    tamanhoOcupado += tamanhoCarro + 3;
    LinkedQueue<Carro>::enqueue(data);
}

Carro Pista::dequeue() {
    if (empty()) {
        throw std::out_of_range("");
    }
    tamanhoOcupado -= (front().getTamanho() + 3);
    return LinkedQueue<Carro>::dequeue();
}

double Pista::getVelocidade() const {
    return velocidade;
}

double Pista::getTamanhoMax() const {
    return tamanhoMax;
}

double Pista::getTamanhoOcupado()  const {
    return tamanhoOcupado;
}

double Pista::getEspacoLivre() const {
    return tamanhoMax - tamanhoOcupado;
}

int Pista::getTempoGeracao() const {
    srand(time(NULL));
    int var = rand() % (t_var * 2);
    int tempo = t_ger_carro - t_var + var;
    return tempo;
}

bool Pista::canFit(Carro carro) {
    if (carro.getTamanho() + 3 + tamanhoOcupado <= tamanhoMax) {
        return true;
    }
    return false;
}

Pista ** Pista::getEntradas() {
    return entradas;
}

void Pista::setEntradas(Pista ** entradas) {
    this->entradas = entradas;
}
