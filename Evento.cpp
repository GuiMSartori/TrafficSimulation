#include "Evento.h"

Evento::Evento(void * dado, int tempo_ev, EVENT_TYPE tipo_ev) {
    this->tempo = tempo_ev;
    this->tipo = tipo_ev;
    this->dado = dado;
}

bool Evento::operator>(const Evento& ev) const {
    return tempo > ev.getTempo();
}

int Evento::getTempo() const {
    return tempo;
}

EVENT_TYPE Evento::getTipo() const {
    return tipo;
}

void * Evento::getDado() const {
    return dado;
}

void Evento::setTempo(int tempo) {
    this->tempo = tempo;
}
