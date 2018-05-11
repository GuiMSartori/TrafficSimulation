#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "Pista.cpp"

class Semaforo {
public:
    Semaforo(structures::DoublyLinkedList<Pista *> * saida, int ** probabilidades);
    ~Semaforo();
    void mudaSinal();
    void trocaDePista(int index, int destino);
    bool isAberto(int index);
    bool isFechado();

    int gerarDestino(int index);

    structures::DoublyLinkedList<Pista *> * getSaidas();
    int getPistaAberta();
private:
    int index_aberto;
    bool sinal[4];
    structures::DoublyLinkedList<Pista *> * saida;
    int ** probabilidades;
};

#endif /* SEMAFORO_H */
