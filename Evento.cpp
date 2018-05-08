#include "Evento.h"

Evento::Evento(int index_semaforo, int index_pista, int index_destino, int tempo_ev, EVENT_TYPE tipo_ev) {
    this->index_semaforo = index_semaforo;
    this->index_pista = index_pista;
    this->index_destino = index_destino;
    this->tempo = tempo_ev;
    this->tipo = tipo_ev;
}


int Evento::getSemaforo() {
    return index_semaforo;
}

int Evento::getSemaforo() const {
    return index_semaforo;
}


int Evento::getPista() {
    return index_pista;
}

int Evento::getPista() const {
    return index_pista;
}

int Evento::getDestino() {
    return index_destino;
}

int Evento::getDestino() const {
    return index_destino;
}


int Evento::getTempo() {
    return tempo;
}

int Evento::getTempo() const {
    return tempo;
}

EVENT_TYPE Evento::getTipo() {
    return tipo;
}

EVENT_TYPE Evento::getTipo() const {
    return tipo;
}

void Evento::setTempo(int tempo) {
    this->tempo = tempo;
}
