#ifndef PISTA_H
#define PISTA_H

#include <cstdint>
#include "LinkedQueue.h"
#include "Carro.h"
#include "array_list.h"

class Pista : public LinkedQueue<Carro> {
public:
    Pista(double tamanhoMax, double velocidade, double t_ger_carro, double var_t);

    void enqueue(const Carro& carro);
    Carro dequeue();

    double getVelocidade();
    double getTamanhoMax();
    double getTamanhoOcupado();
    double getEspacoLivre();

    void setProbabilidades(structures::ArrayList<double> probabilidades);
    void setEntradas(structures::ArrayList<Pista *> entradas);
    
    structures::ArrayList<double>& getProbabilidades();
    structures::ArrayList<Pista *>& getEntradas();
    
    bool canFit(Carro carro);
private:
    double tamanhoMax;
    double tamanhoOcupado;
    double velocidade;
    double t_ger_carro;
    double var_t;
    
    structures::ArrayList<Pista *> entradas;
    
    structures::ArrayList<double> probabilidades;
};

#endif /* PISTA_H */
