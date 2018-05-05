#ifndef EVENTO_H
#define EVENTO_H

enum EVENT_TYPE {
    chegada_carro, mudanca_semaforo, chegada_semaforo, troca_pista
};

class Evento {
public:
    Evento(int tempo_ev, EVENT_TYPE tipo_ev);

    int getTempo() const;

    void setTemp(int tempo);

    EVENT_TYPE getTipo() const;

    bool operator>(const Evento& ev) const;
private:
    int tempo;
    EVENT_TYPE tipo;
};

#endif /* EVENTO_H */

