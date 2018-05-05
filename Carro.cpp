#include "Carro.h"

Carro::Carro(float tam) {
    tamanho = tam;
}

float Carro::getTamanho() {
    return tamanho;
}

const float Carro::getTamanho() const{
    return tamanho;
}
