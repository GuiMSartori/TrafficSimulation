#ifndef EVENTO_H
#define EVENTO_H

#include "Pista.h"

enum EVENT_TYPE {
    GERACAO_DE_CARRO, MUDANCA_DO_SEMAFORO, CHEGADA_AO_SEMAFORO, TROCA_DE_PISTA
};

class Evento {
public:
    Evento(Pista * pista, int tempo_ev, EVENT_TYPE tipo_ev);

    int getTempo() const;

    Pista * getPista() const;
    EVENT_TYPE getTipo() const;

    bool operator>(const Evento& ev) const;
private:
    int tempo;
    EVENT_TYPE tipo;
    Pista * pista;
};

#endif /* EVENTO_H */

