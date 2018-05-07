#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "Pista.cpp"

class Semaforo {
public:
    Semaforo(structures::ArrayList<Pista *> saida, double ** probabilidades);
    ~Semaforo();
    void mudaSinal();
    void trocaDePista(int index, int destino);
    bool isAberto(int index);

    int gerarDestino(int index);

    Pista * getSaida(int index);
    int getPistaAberta();
private:
    int index_aberto;
    bool sinal[4];
    structures::ArrayList<Pista *> saida;
    double ** probabilidades;
};

#endif /* SEMAFORO_H */
