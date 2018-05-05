#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "Pista.h"

class Semaforo {
public:
    Semaforo(structures::ArrayList<Pista *> saida, structures::ArrayList<Pista *> entrada, structures::ArrayList<double> probabilidades);
    void mudaSinal();
    void trocaDePista(Pista * pista);
    bool isAberto();
private:
    bool aberto;
    structures::ArrayList<Pista *> saida;
    structures::ArrayList<Pista *> entrada;
    structures::ArrayList<double> probabilidades;
};

#endif /* SEMAFORO_H */
