#ifndef EVENTO_H
#define EVENTO_H

#include "Pista.h"

enum EVENT_TYPE {
    GERACAO_DE_CARRO, MUDANCA_DO_SEMAFORO, CHEGADA_AO_SEMAFORO, TROCA_DE_PISTA
};

class Evento {
public:
    Evento(void * dado, int tempo_ev, EVENT_TYPE tipo_ev);

    int getTempo() const;
    void * getDado() const;
    EVENT_TYPE getTipo() const;

    void setTempo(int tempo);
    
    bool operator>(const Evento& ev) const;
private:
    int tempo;
    EVENT_TYPE tipo;
    void * dado;
};

#endif /* EVENTO_H */

