#ifndef PISTA_H
#define PISTA_H

#include <cstdint>
#include "LinkedQueue.h"
#include "Carro.h"
#include "array_list.h"

class Pista: public LinkedQueue<Carro> {
  public:
      Pista(float tamanhoMax, float velocidade, structures::ArrayList<Pista *> saida);

      void enqueue(const Carro& carro);
      Carro dequeue();

      float getVelocidade();
      float getTamanhoMax();
      float getTamanhoOcupado();
      float getEspacoLivre();
      
      bool canFit(Carro carro);
  private:
      structures::ArrayList<Pista *> saida;
      
      float tamanhoMax;
      float tamanhoOcupado;
      float velocidade;
};

#endif /* PISTA_H */
