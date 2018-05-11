#ifndef PISTA_H
#define PISTA_H

#include <cstdint>
#include "LinkedQueue.h"
#include "Carro.cpp"
#include "array_list.h"

class Pista : public LinkedQueue<Carro> {
public:
    Pista(double tamanhoMax, double velocidade, int t_ger_carro, int t_var);
    ~Pista();

    void enqueue(const Carro& carro);
    Carro dequeue();

    double getVelocidade() const;
    double getTamanhoMax() const;
    double getTamanhoOcupado() const;
    double getEspacoLivre() const;

    int getTempoGeracao() const;

    void setEntradas(Pista ** entradas);

    Pista ** getEntradas();

    bool canFit(Carro carro);
private:
    double tamanhoMax;
    double tamanhoOcupado;
    double velocidade;
    int t_ger_carro;
    int t_var;

    Pista ** entradas;
};

#endif /* PISTA_H */
