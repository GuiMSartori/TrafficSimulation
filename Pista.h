#ifndef PISTA_H
#define PISTA_H

#include <cstdint>
#include "LinkedQueue.h"
#include "Carro.h"

class Pista: public LinkedQueue<Carro> {
  public:
      Pista(float tamanhoMax, float velocidade);

      void enqueue(const Carro& carro);
      Carro dequeue();

      float getVelocidade();
      float getTamanhoMax();
      float getTamanhoOcupado();
      float getEspacoLivre();

  private:
      float tamanhoMax;
      float tamanhoOcupado;
      float velocidade;
};

#endif /* PISTA_H */
