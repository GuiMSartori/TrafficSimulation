#ifndef EVENTO_H
#define EVENTO_H

#include "Pista.h"

enum EVENT_TYPE {
    GERACAO_DE_CARRO, MUDANCA_DO_SEMAFORO, CHEGADA_AO_FIM_DA_PISTA, TROCA_DE_PISTA
};

class Evento {
public:
    Evento(int index_semaforo, int index_pista, int index_destino, int tempo_ev, EVENT_TYPE tipo_ev);

    int getSemaforo();
    int getSemaforo() const;
    int getPista();
    int getPista() const;
    int getDestino();
    int getDestino() const;
    int getTempo();
    int getTempo() const;
    EVENT_TYPE getTipo();
    EVENT_TYPE getTipo() const;

    void setTempo(int tempo);
private:
    int index_semaforo;
    int index_pista;
    int index_destino;
    int tempo;
    EVENT_TYPE tipo;
    int * dado;
};

#endif /* EVENTO_H */
