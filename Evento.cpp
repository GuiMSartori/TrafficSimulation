#include "Evento.h"

bool Evento::operator >(const Evento& ev) const {
    return tempo_ev > ev.getTempoEv();
}

int Evento::getTempoCr() const {
    return tempo_criacao;
}

int Evento::getTempoEv() const {
    return tempo_ev;
}

EVENT_TYPE Evento::getTipo() const {
    return tipo_ev;
}

void Evento::setTempEv(int tempo) {
    tempo_ev = tempo;
}