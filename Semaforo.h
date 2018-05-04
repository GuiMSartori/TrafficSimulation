#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "Pista.h"

class Semaforo {
public:
    Semaforo(Pista * saida, structures::ArrayList<Pista *> entrada, structures::ArrayList<float> probabilidades);
    ~Semaforo();
    void mudaSinal();
    void trocaDePista();
    bool isAberto();
private:
    bool aberto;
    Pista * saida;
    structures::ArrayList<Pista *> entrada;
    structures::ArrayList<float> probabilidades;
};

#endif /* SEMAFORO_H */
