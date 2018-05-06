#ifndef PISTA_H
#define PISTA_H

#include <cstdint>
#include "LinkedQueue.h"
#include "Carro.h"
#include "array_list.h"

class Pista : public LinkedQueue<Carro> {
public:
    Pista(double tamanhoMax, double velocidade, int t_ger_carro, int var_t);
    ~Pista();

    void enqueue(const Carro& carro);
    Carro dequeue();

    double getVelocidade();
    double getTamanhoMax();
    double getTamanhoOcupado();
    double getEspacoLivre();

    int getTempoGeracao();

    void setEntradas(structures::ArrayList<Pista *> * entradas);

    structures::ArrayList<Pista *> * getEntradas();

    bool canFit(Carro carro);
private:
    double tamanhoMax;
    double tamanhoOcupado;
    double velocidade;
    int t_ger_carro;
    int var_t;

    structures::ArrayList<Pista *> * entradas;
};

#endif /* PISTA_H */
