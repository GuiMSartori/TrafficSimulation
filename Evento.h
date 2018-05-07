#ifndef EVENTO_H
#define EVENTO_H

#include "Pista.h"

enum EVENT_TYPE {
    GERACAO_DE_CARRO, MUDANCA_DO_SEMAFORO, CHEGADA_AO_SEMAFORO, TROCA_DE_PISTA
};

class Evento {
public:
    Evento(int * dado, int tempo_ev, EVENT_TYPE tipo_ev);

    int getTempo();
    int getTempo() const;
    int getFonte();
    int getFonte() const;
    int * getDado();
    int * getDado() const;
    EVENT_TYPE getTipo();
    EVENT_TYPE getTipo() const;

    void setTempo(int tempo);

    bool operator>(const Evento& ev);
    bool operator>(const Evento& ev) const;
private:
    int index_fonte;
    int tempo;
    EVENT_TYPE tipo;
    int * dado;
};

#endif /* EVENTO_H */
