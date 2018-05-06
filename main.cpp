#include <cstdlib>
#include <iostream>
#include <fstream>
#include "linked_list.h"
#include "LinkedQueue.h"
#include "Evento.h"
#include "Semaforo.h"

structures::LinkedList<Evento> relogio;
structures::LinkedList<Pista *> pistas;
structures::LinkedList<Semaforo *> semaforos;

int tempo_simulacao;
int tempo_simulado;

void init();
void initPistas();
void initSemaforos();
void setEntradasPistas();
void end();

int main() {
    init();
    while (tempo_simulado < tempo_simulacao) {

        tempo_simulado++;
    }
    end();
    return 0;
}

void init() {
    tempo_simulado = 0;

    std::ifstream ifs;
    ifs.open("tempo_simulado.txt");
    if (ifs.is_open()) {
        char linha[40];
        ifs.getline(linha, 40);
        tempo_simulacao = std::atoi(linha);
        ifs.close();
    } else
        std::cout << "Nao foi possivel abrir tempo_simulado.txt" << std::endl;


    initPistas();

    initSemaforos();

    setEntradasPistas();

    relogio = structures::LinkedList<Evento>();
    relogio.insert_sorted(Evento(0, chegada_carro));

}

void initPistas() {
    pistas = structures::LinkedList<Pista>();
    std::ifstream ifs;
    ifs.open("pistas.txt");
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            char linha1[40], linha2[40], linha3[40], linha4[40];
            ifs.getline(linha1, 40);

            ifs.getline(linha1, 40);
            ifs.getline(linha2, 40);
            ifs.getline(linha3, 40);
            ifs.getline(linha4, 40);

            Pista * pista = new Pista(std::atof(linha1), std::atof(linha2), std::atof(linha3), std::atof(linha4));
            pistas.push_back(pista);
        }
        ifs.close();
    } else
        std::cout << "Nao foi possivel abrir pistas.txt" << std::endl;
}

void initSemaforos() {
    semaforos = structures::LinkedList<Semaforo *>();

    structures::ArrayList<structures::ArrayList<double>> probs_sem1 = structures::ArrayList<structures::ArrayList<double>>(4);
    structures::ArrayList<structures::ArrayList<double>> probs_sem2 = structures::ArrayList<structures::ArrayList<double>>(4);

    std::ifstream ifs;
    ifs.open("semaforo.txt");
    if (ifs.is_open()) {
        for (int i = 0; i < 4; i++) {
            structures::ArrayList<double> probs_pista = new structures::ArrayList<double>(3);
            char linha[40];

            ifs.getline(linha, 40);

            for (int i = 0; i < 3; i++) {
                ifs.getline(linha, 40);
                probs_pista.push_back(atof(linha));
            }

            probs_sem1.push_back(probs_pista);
        }
        for (int i = 0; i < 4; i++) {
            structures::ArrayList<double> probs_pista = new structures::ArrayList<double>(3);
            char linha[40];

            ifs.getline(linha, 40);

            for (int i = 0; i < 3; i++) {
                ifs.getline(linha, 40);
                probs_pista.push_back(atof(linha));
            }

            probs_sem2.push_back(probs_pista);
        }
        ifs.close();
    } else
        std::cout << "Nao foi possivel abrir semaforo.txt" << std::endl;

    structures::ArrayList<Pista *> pistas_sem1 = structures::ArrayList<Pista*>(4);
    structures::ArrayList<Pista *> pistas_sem2 = structures::ArrayList<Pista*>(4);

    for (int i = 0; i < 4; i++) {
        pistas_sem1.push_back(pistas.at(i));
    }
    for (int i = 4; i < 8; i++) {
        pistas_sem2.push_back(pistas.at(i));
    }

    semaforos.push_back(new Semaforo(pistas_sem1, probs_sem1));
    semaforos.push_back(new Semaforo(pistas_sem2, probs_sem2));
}

void setEntradasPistas() {
    structures::ArrayList<Pista *> entradas[8];

    for (int i = 0; i < 8; i++) {
        entradas[i] = structures::ArrayList<Pista *>(3);
    }

    entradas[0].push_back(pistas.at(4));
    entradas[0].push_back(pistas.at(9));
    entradas[0].push_back(pistas.at(10));

    entradas[1].push_back(pistas.at(4));
    entradas[1].push_back(pistas.at(8));
    entradas[1].push_back(pistas.at(10));

    entradas[2].push_back(pistas.at(4));
    entradas[2].push_back(pistas.at(9));
    entradas[2].push_back(pistas.at(8));

    entradas[3].push_back(pistas.at(8));
    entradas[3].push_back(pistas.at(9));
    entradas[3].push_back(pistas.at(10));

    entradas[4].push_back(pistas.at(12));
    entradas[4].push_back(pistas.at(11));
    entradas[4].push_back(pistas.at(13));

    entradas[5].push_back(pistas.at(12));
    entradas[5].push_back(pistas.at(3));
    entradas[5].push_back(pistas.at(13));

    entradas[6].push_back(pistas.at(12));
    entradas[6].push_back(pistas.at(11));
    entradas[6].push_back(pistas.at(3));

    entradas[7].push_back(pistas.at(11));
    entradas[7].push_back(pistas.at(3));
    entradas[7].push_back(pistas.at(13));

    for (int i = 0; i < 8; i++) {
        pistas.at(i)->setEntradas(entradas[i]);
    }
}
