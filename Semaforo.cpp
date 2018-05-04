#include "Semaforo.h"


Semaforo::Semaforo(Pista * saida, structures::ArrayList<Pista *> entrada, structures::ArrayList<float> probabilidades) {
    this->saida = saida;
    this->entrada = entrada;
    this->probabilidades = probabilidades;
}

Semaforo::~Semaforo() {
    delete saida;
}
    
void Semaforo::mudaSinal() {
    if (aberto) {
        aberto = false;
    } else {
        aberto = true;
    }
}
    
void Semaforo::trocaDePista() {
    srand(time(NULL));
    rand();
}
    
bool Semaforo::isAberto() {
    return aberto;
}
    