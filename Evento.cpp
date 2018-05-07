#include "Evento.h"

Evento::Evento(int * dado, int tempo_ev, EVENT_TYPE tipo_ev) {
    this->index_fonte = index_fonte;
    this->tempo = tempo_ev;
    this->tipo = tipo_ev;
    this->dado = new int[3];
    this->dado = dado;


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

int Evento::getFonte() const {
    return index_fonte;
}

int Evento::getFonte() {
    return index_fonte;
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
