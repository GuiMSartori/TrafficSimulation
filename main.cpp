#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "linked_list.h"
#include "LinkedQueue.h"
#include "Evento.h"
#include "Semaforo.h"

structures::LinkedList<Evento> relogio;
structures::LinkedList<Pista *> pistas;
structures::LinkedList<Pista *> sumidouros;
structures::LinkedList<Pista *> fontes;
structures::LinkedList<Semaforo *> semaforos;

int tempo_simulacao;
int tempo_simulado;
int periodo_semaforo;

void init();
void initPistas();
void initSemaforos();
void setEntradasPistas();
void initRelogio();

void execEventos();
void geracaoDeCarro(Evento evento);
void mudancaDoSemaforo();
void chegadaAoSemaforo(Evento evento);
int calculaTempoDeTrocaDePista(int * index);
void trocaDePista(Evento evento);

void end();

int main() {
    init();
    while (tempo_simulado < tempo_simulacao) {
        execEventos();
        tempo_simulado++;
    }
    end();
    return 0;
}

void init() {
    tempo_simulado = 0;

    std::ifstream ifs;
    ifs.open("tempo_simulacao.txt");
    if (ifs.is_open()) {
        char linha[40], linha2[40];
        ifs.getline(linha, 40);
        tempo_simulacao = std::atoi(linha);
        ifs.getline(linha2, 40);
        periodo_semaforo = std::atoi(linha2);
        ifs.close();
    } else
        std::cout << "Nao foi possivel abrir tempo_simulacao.txt" << std::endl;

    initPistas();
    initSemaforos();
    setEntradasPistas();
    initRelogio();
}

void initPistas() {
    pistas = structures::LinkedList<Pista *>();
    sumidouros = structures::LinkedList<Pista *>();
    fontes = structures::LinkedList<Pista *>();

    std::ifstream ifs;
    ifs.open("pistas.txt");
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            char linha[40], linha1[40], linha2[40], linha3[40], linha4[40];
            ifs.getline(linha, 40);

            ifs.getline(linha1, 40);
            ifs.getline(linha2, 40);
            ifs.getline(linha3, 40);
            ifs.getline(linha4, 40);

            Pista * pista = new Pista(std::atof(linha1), std::atof(linha2), std::atoi(linha3), std::atoi(linha4));
            pistas.push_back(pista);
        }
        ifs.close();
    } else
        std::cout << "Nao foi possivel abrir pistas.txt" << std::endl;

    for (int i = 8; i < 14; i++) {
        sumidouros.push_back(pistas.at(i));
    }

    for (int i = 0; i < 8; i++) {
        if (i == 3) {
            i = 5;
        }
        fontes.push_back(pistas.at(i));
    }
}

void initSemaforos() {
    semaforos = structures::LinkedList<Semaforo *>();

    structures::ArrayList<double> * probs_sem1 = new structures::ArrayList<double>[4];
    structures::ArrayList<double> * probs_sem2 = new structures::ArrayList<double>[4];


    std::ifstream ifs;
    ifs.open("semaforo.txt");
    if (ifs.is_open()) {
        for (int i = 0; i < 4; i++) {
            structures::ArrayList<double> probs_pista = structures::ArrayList<double>(3);
            char linha[40];

            ifs.getline(linha, 40);

            for (int i = 0; i < 3; i++) {
                ifs.getline(linha, 40);
                probs_pista.push_back(atof(linha));
            }

            probs_sem1[i] = probs_pista;
        }
        for (int i = 0; i < 4; i++) {
            structures::ArrayList<double> probs_pista = structures::ArrayList<double>(3);
            char linha[40];

            ifs.getline(linha, 40);

            for (int i = 0; i < 3; i++) {
                ifs.getline(linha, 40);
                probs_pista.push_back(atof(linha));
            }

            probs_sem2[i] = probs_pista;
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
    structures::ArrayList<Pista *> * entradas[8];

    for (int i = 0; i < 8; i++) {
        entradas[i] = new structures::ArrayList<Pista *>(3);
    }

    entradas[0]->push_back(pistas.at(4));
    entradas[0]->push_back(pistas.at(9));
    entradas[0]->push_back(pistas.at(10));

    entradas[1]->push_back(pistas.at(4));
    entradas[1]->push_back(pistas.at(8));
    entradas[1]->push_back(pistas.at(10));

    entradas[2]->push_back(pistas.at(4));
    entradas[2]->push_back(pistas.at(9));
    entradas[2]->push_back(pistas.at(8));

    entradas[3]->push_back(pistas.at(8));
    entradas[3]->push_back(pistas.at(9));
    entradas[3]->push_back(pistas.at(10));

    entradas[4]->push_back(pistas.at(12));
    entradas[4]->push_back(pistas.at(11));
    entradas[4]->push_back(pistas.at(13));

    entradas[5]->push_back(pistas.at(12));
    entradas[5]->push_back(pistas.at(3));
    entradas[5]->push_back(pistas.at(13));

    entradas[6]->push_back(pistas.at(12));
    entradas[6]->push_back(pistas.at(11));
    entradas[6]->push_back(pistas.at(3));

    entradas[7]->push_back(pistas.at(11));
    entradas[7]->push_back(pistas.at(3));
    entradas[7]->push_back(pistas.at(13));

    for (int i = 0; i < 8; i++) {
        pistas.at(i)->setEntradas(entradas[i]);
    }
}

void initRelogio() {
    relogio = structures::LinkedList<Evento>();
    for (int i = 0; i < fontes.size(); i++) {
        relogio.insert_sorted(Evento(fontes.at(i), fontes.at(i)->getTempoGeracao(), GERACAO_DE_CARRO));
    }
    relogio.insert_sorted(Evento(NULL, periodo_semaforo, MUDANCA_DO_SEMAFORO));
}

void execEventos() {
    while (tempo_simulado = relogio.at(0).getTempo()) {
        Evento evento = relogio.pop_front();
        switch (evento.getTipo()) {
            case GERACAO_DE_CARRO:
                geracaoDeCarro(evento);
                break;

            case MUDANCA_DO_SEMAFORO:
                mudancaDoSemaforo();
                break;

            case CHEGADA_AO_SEMAFORO:
                chegadaAoSemaforo(evento);
                break;

            case TROCA_DE_PISTA:
                trocaDePista(evento);
                break;

            default:
                break;
        }
    }
}

void geracaoDeCarro(Evento evento) {
    std::cout << "Gerando carro..." << std::endl;
    srand(time(NULL));
    int var_size = rand() % 4;
    Carro carro = Carro(2 + var_size);
    Pista * pista = (Pista *) evento.getDado();
    try {
        pista->enqueue(carro);
        relogio.insert_sorted(Evento(pista, tempo_simulado + (int) pista->getTamanhoMax() / pista->getVelocidade(), CHEGADA_AO_SEMAFORO));
    } catch (std::out_of_range ex) {
    }
    relogio.insert_sorted(Evento((void *) pista, tempo_simulado + pista->getTempoGeracao(), GERACAO_DE_CARRO));
    std::cout << "Carro gerado." << std::endl;
}

void mudancaDoSemaforo() {
    std::cout << "Mudando semaforos..." << std::endl;
    semaforos.at(0)->mudaSinal();
    semaforos.at(1)->mudaSinal();

    relogio.insert_sorted(Evento(NULL, tempo_simulado + periodo_semaforo, MUDANCA_DO_SEMAFORO));
    std::cout << "Semaforos mudados." << std::endl;
}

void chegadaAoSemaforo(Evento evento) {
    std::cout << "Chegando ao semaforo..." << std::endl;
    int * index = new int[3];
    index[0] = -1;
    index[1] = -1;
    index[2] = -1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if ((Pista *) evento.getDado() == semaforos.at(i)->getSaida(j)) {
                index[0] = j;
                index[1] = i;
                break;
            }
        }
        if (index[0] != -1) break;
    }

    index[2] = semaforos.at(index[0])->gerarDestino(index[1]);

    int tempo_de_troca_de_pista = calculaTempoDeTrocaDePista(index);

    relogio.insert_sorted(Evento((void *) index, tempo_de_troca_de_pista, TROCA_DE_PISTA));
    std::cout << "Chegou com sucesso." << std::endl;
}

int calculaTempoDeTrocaDePista(int * index) {
    int tempo_de_troca_de_pista = tempo_simulado;

    if (!semaforos.at(index[0])->isAberto(index[1])) {
        int pista_aberta = semaforos.at(index[0])->getPistaAberta();

        tempo_de_troca_de_pista += periodo_semaforo - (tempo_simulado % periodo_semaforo);

        if (pista_aberta < index[1]) {
            tempo_de_troca_de_pista += (index[1] - pista_aberta - 1) * periodo_semaforo * 2;
        } else {
            tempo_de_troca_de_pista += (4 - pista_aberta + index[1] - 1) * 2 * periodo_semaforo;
        }

        if (!semaforos.at(index[0])->isAberto(pista_aberta)) {
            tempo_de_troca_de_pista -= periodo_semaforo;
        }
    }
    return tempo_de_troca_de_pista;
}

void trocaDePista(Evento evento) {
    std::cout << "Trocando de pista." << std::endl;

    int * index = new int[3];
    for (int i = 0; i < 3; i++) {
        index[i] = ((int *) evento.getDado())[i];
    }
    try {
        semaforos.at(index[0])->trocaDePista(index[1], index[2]);
        std::cout << "Trocou com sucesso." << std::endl;
    } catch (std::out_of_range ex) {
        relogio.insert_sorted(Evento((void *) index, evento.getTempo() + 1, TROCA_DE_PISTA));

        for (int i = 0; i < relogio.size(); i++) {
            if (relogio.at(i).getDado() == evento.getDado() && relogio.at(i).getTipo() == CHEGADA_AO_SEMAFORO) {
                relogio.at(i).setTempo(relogio.at(i).getTempo() + 1);
            }
        }
    }
    delete (int *) evento.getDado();
}

void end() {
    std::cout << "Finalizando..." << std::endl;
    for (int i = 0; i < pistas.size(); i++) {
        delete pistas.pop_front();
    }
    for (int i = 0; i < semaforos.size(); i++) {
        delete semaforos.pop_front();
    }
    for (int i = 0; i < sumidouros.size(); i++) {
        delete sumidouros.pop_front();
    }
    for (int i = 0; i < fontes.size(); i++) {
        delete fontes.pop_front();
    }
    std::cout << "Simulacao finalizada." << std::endl;

}