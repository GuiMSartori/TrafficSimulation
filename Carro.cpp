#include "Carro.h"

Carro::Carro(float tam) {
    tamanho = tam;
}


Carro::~Carro() {
}

float Carro::getPosicao() {
    return posicao;
}

const float Carro::getPosicao() const{
    return posicao;
}

void Carro::setPosicao(float pos) {
    posicao = pos;
}

float Carro::getTamanho() {
    return tamanho;
}

const float Carro::getTamanho() const{
    return tamanho;
}
