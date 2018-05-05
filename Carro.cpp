#include "Carro.h"

Carro::Carro(double tam) {
    tamanho = tam;
}

double Carro::getTamanho() {
    return tamanho;
}

const double Carro::getTamanho() const {
    return tamanho;
}
