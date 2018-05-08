#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "Pista.cpp"

class Semaforo {
public:
    Semaforo(structures::LinkedList<Pista *> * saida, double ** probabilidades);
    ~Semaforo();
    void mudaSinal();
    void trocaDePista(int index, int destino);
    bool isAberto(int index);

    int gerarDestino(int index);

    structures::LinkedList<Pista *> * getSaidas();
    int getPistaAberta();
private:
    int index_aberto;
    bool sinal[4];
    structures::LinkedList<Pista *> * saida;
    double ** probabilidades;
};

#endif /* SEMAFORO_H */
