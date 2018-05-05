#include <cstdlib>
#include <iostream>
#include <fstream>
#include "linked_list.h"
#include "LinkedQueue.h"
#include "Evento.h"
#include "Semaforo.h"

structures::LinkedList<Evento> relogio;
structures::LinkedList<Pista> pistas;
structures::LinkedList<Semaforo> semaforos;

int tempo_total;
int tempo_simulado;

void init();
void initPistas();

int main(int argc, char** argv) {
    init();

    tempo_simulado++;
    return 0;
}

void init() {
    tempo_simulado = 0;

    relogio = structures::LinkedList<Evento>();
    relogio.insert_sorted(Evento(0, chegada_carro));

    semaforos = structures::LinkedList<Semaforo>();

    initPistas();



}

void initPistas() {
    pistas = structures::LinkedList<Pista>();
    std::ifstream ifs;
    ifs.open("pistas.txt");
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            char linha1[4], linha2[4], linha3[4], linha4[4];
            ifs.getline(linha1, 4);
            ifs.getline(linha2, 4);
            ifs.getline(linha3, 4);
            ifs.getline(linha4, 4);

            Pista pista = pista(std::atof(linha1), std::atof(linha2), std::atof(linha3), std::atof(linha4));
            pistas.push_back(pista);

            ifs.getline(linha1, 4);
        }
    } else
        std::cout << "Nao foi possivel abrir..." << std::endl;
}