#include "Evento.h"

Evento::Evento(int * dado, int tempo_ev, EVENT_TYPE tipo_ev) {
    this->tempo = tempo_ev;
    this->tipo = tipo_ev;
    this->dado = dado;
}

Evento::~Evento() {
    delete[] dado;
}

bool Evento::operator>(const Evento& ev) const {
    return tempo > ev.getTempo();
}

bool Evento::operator>(const Evento& ev) {
    return tempo > ev.getTempo();
}


int Evento::getTempo() const {
    return tempo;
}

int Evento::getTempo() {
    return tempo;
}

EVENT_TYPE Evento::getTipo() const {
    return tipo;
}

EVENT_TYPE Evento::getTipo() {
    return tipo;
}

int * Evento::getDado() const {
    return dado;
}

int * Evento::getDado() {
    return dado;
}

void Evento::setTempo(int tempo) {
    this->tempo = tempo;
}
