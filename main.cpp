#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "linked_list.h"
#include "LinkedQueue.h"
#include "Evento.cpp"
#include "Semaforo.cpp"

structures::LinkedList<Evento *> relogio;
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
void geracaoDeCarro(Evento * evento);
void mudancaDoSemaforo();
void chegadaAoSemaforo(Evento * evento);
void trocaDePista(Evento * evento);
void insereNoRelogio(Evento * evento);

void finalize();

int main() {
    init();
    std::cout << tempo_simulacao << '\n';
    while (tempo_simulado < tempo_simulacao) {
        execEventos();
        tempo_simulado++;
    }
    finalize();
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
    std::cout << "initPistas" << '\n';
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
            pistas.push_back(new Pista(std::atof(linha1), std::atof(linha2), std::atoi(linha3), std::atoi(linha4)));
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
    std::cout << "fim initPistas" << '\n';
}

void initSemaforos() {
    std::cout << "initSemaforos" << '\n';
    semaforos = structures::LinkedList<Semaforo *>();

    double ** probs_sem1 = new double * [4];
    double ** probs_sem2 = new double * [4];

    std::ifstream ifs;
    ifs.open("semaforo.txt");
    if (ifs.is_open()) {
        for (int i = 0; i < 4; i++) {
            probs_sem1[i] = new double[3];

            char linha[40];

            ifs.getline(linha, 40);

            for (int j = 0; j < 3; j++) {
                ifs.getline(linha, 40);
                probs_sem1[i][j] = (atof(linha));
            }
        }
        for (int i = 0; i < 4; i++) {
            probs_sem2[i] = new double[3];

            char linha[40];

            ifs.getline(linha, 40);

            for (int j = 0; j < 3; j++) {
                ifs.getline(linha, 40);
                probs_sem2[i][j] = (atof(linha));
            }
        }
        ifs.close();
    } else
        std::cout << "Nao foi possivel abrir semaforo.txt" << std::endl;

    structures::LinkedList<Pista *> * pistas_sem1 = new structures::LinkedList<Pista *>();
    structures::LinkedList<Pista *> * pistas_sem2 = new structures::LinkedList<Pista *>();

    for (int i = 0; i < 4; i++) {
        pistas_sem1->push_back(pistas.at(i));
    }
    for (int i = 4; i < 8; i++) {
        pistas_sem2->push_back(pistas.at(i));
    }
    semaforos.push_back(new Semaforo(pistas_sem1, probs_sem1));
    semaforos.push_back(new Semaforo(pistas_sem2, probs_sem2));
    std::cout << "fim initSemaforos" << '\n';
}

void setEntradasPistas() {
    std::cout << "setEntradasPistas" << '\n';
    Pista *** entradas = new Pista **[8];

    for (int i = 0; i < 8; i++) {
        entradas[i] = new Pista *[3];
    }

    entradas[0][0] = pistas.at(4);
    entradas[0][1] = pistas.at(9);
    entradas[0][2] = pistas.at(10);

    entradas[1][0] = pistas.at(4);
    entradas[1][1] = pistas.at(8);
    entradas[1][2] = pistas.at(10);

    entradas[2][0] = pistas.at(4);
    entradas[2][1] = pistas.at(9);
    entradas[2][2] = pistas.at(8);

    entradas[3][0] = pistas.at(8);
    entradas[3][1] = pistas.at(9);
    entradas[3][2] = pistas.at(10);

    entradas[4][0] = pistas.at(12);
    entradas[4][1] = pistas.at(11);
    entradas[4][2] = pistas.at(13);

    entradas[5][0] = pistas.at(12);
    entradas[5][1] = pistas.at(3);
    entradas[5][2] = pistas.at(13);

    entradas[6][0] = pistas.at(12);
    entradas[6][1] = pistas.at(11);
    entradas[6][2] = pistas.at(3);

    entradas[7][0] = pistas.at(11);
    entradas[7][1] = pistas.at(3);
    entradas[7][2] = pistas.at(13);

    for (int i = 0; i < 8; i++) {
        pistas.at(i)->setEntradas(entradas[i]);
    }
    std::cout << "fim setEntradasPistas" << '\n';
}

void initRelogio() {
    std::cout << "initRelogio" << '\n';
    relogio = structures::LinkedList<Evento *>();
    insereNoRelogio(new Evento(-1, -1, -1, periodo_semaforo, MUDANCA_DO_SEMAFORO));
    for (int i = 0; i < fontes.size(); i++) {
        int sem_index = (i < 3) ? 0 : 1;
        int pista_index = semaforos.at(sem_index)->getSaidas()->find(fontes.at(i));
        insereNoRelogio(new Evento(sem_index, pista_index, sem_index, fontes.at(i)->getTempoGeracao(), GERACAO_DE_CARRO));
    }
    std::cout << "fim initRelogio" << '\n';
}

void execEventos() {
    while (tempo_simulado == relogio.at(0)->getTempo()) {
        std::cout << tempo_simulado << '\n';
        Evento * evento = relogio.pop_front();
        switch (evento->getTipo()) {
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
        }
        delete evento;
    }
}

void geracaoDeCarro(Evento * evento) {
    std::cout << "Gerando carro..." << std::endl;

    int sem_index = evento->getSemaforo();
    int pista_index = evento->getPista();
    srand(time(NULL));
    int var_size = rand() % 4;
    Carro carro = Carro(2 + var_size);
    Pista * pista = semaforos.at(sem_index)->getSaidas()->at(pista_index);
    try {
        pista->enqueue(carro);

        int tempo_percurso = (int) (pista->getTamanhoMax() / pista->getVelocidade());
        Evento * eve = new Evento(sem_index, pista_index, -1, tempo_simulado + tempo_percurso, CHEGADA_AO_SEMAFORO);
        insereNoRelogio(eve);

        std::cout << "Carro gerado." << std::endl;
    } catch (std::out_of_range ex) {
        std::cout << "Pista cheia." << std::endl;
    }
    Evento * ev = new Evento(sem_index, pista_index, -1, tempo_simulado + pista->getTempoGeracao(), GERACAO_DE_CARRO);
    insereNoRelogio(ev);
}

void mudancaDoSemaforo() {
    std::cout << "Mudando semaforos..." << std::endl;

    semaforos.at(0)->mudaSinal();
    semaforos.at(1)->mudaSinal();
    int tempo_ev = tempo_simulado;

    if (semaforos.at(0)->isFechado()) {
        tempo_ev += (int) periodo_semaforo/6;
    } else {
        tempo_ev += periodo_semaforo;
    }
    insereNoRelogio(new Evento(-1, -1, -1, tempo_ev, MUDANCA_DO_SEMAFORO));

    std::cout << "Semaforos mudados." << std::endl;
}

void chegadaAoSemaforo(Evento * evento) {
    std::cout << "Chegando ao fim da pista..." << std::endl;

    int sem_index = evento->getSemaforo();
    int pista_index = evento->getPista();

    if (sem_index == -1) {
        sumidouros.at(pista_index)->dequeue();

        std::cout << "Saiu da pista." << std::endl;
        return;
    }

    int index_destino = semaforos.at(sem_index)->gerarDestino(pista_index);

    int tempo = evento->getTempo();
    insereNoRelogio(new Evento(sem_index, pista_index, index_destino, tempo, TROCA_DE_PISTA));
    std::cout << "Chegou ao semaforo." << std::endl;
}

void trocaDePista(Evento * evento) {
    std::cout << "Trocando de pista." << std::endl;

    int sem_index = evento->getSemaforo();
    int pista_index = evento->getPista();
    int des_index = evento->getDestino();

    try {
        semaforos.at(sem_index)->trocaDePista(pista_index, des_index);

        Pista * pista_destino = semaforos.at(sem_index)->getSaidas()->at(pista_index)->getEntradas()[des_index];
        int tempo_percurso = (int) (pista_destino->getTamanhoMax() / pista_destino->getVelocidade());

        if (sumidouros.contains(pista_destino)) {
            int index_pis = sumidouros.find(pista_destino);
            insereNoRelogio(new Evento(-1, index_pis, -1, evento->getTempo() + tempo_percurso, CHEGADA_AO_SEMAFORO));
        } else if (semaforos.at(0)->getSaidas()->contains(pista_destino)) {
            insereNoRelogio(new Evento(0, semaforos.at(0)->getSaidas()->find(pista_destino), -1,
                evento->getTempo() +  tempo_percurso, CHEGADA_AO_SEMAFORO));
        } else {
            insereNoRelogio(new Evento(1, semaforos.at(1)->getSaidas()->find(pista_destino), -1,
                evento->getTempo() +  tempo_percurso, CHEGADA_AO_SEMAFORO));
        }

        std::cout << "Trocou com sucesso." << std::endl;
    } catch (std::out_of_range ex) {
        int tempo_evento;
        if (semaforos.at(sem_index)->isFechado()) {
            Evento * evento;
            for (int i = 0; i < relogio.size(); i++) {
                if (relogio.at(i)->getTipo() == MUDANCA_DO_SEMAFORO) {
                    evento = relogio.at(i);
                    break;
                }
            }
            tempo_evento = evento->getTempo() + 1;
            std::cout << "Semaforo fechado." << std::endl;
        } else {
            tempo_evento = evento->getTempo() + 1;
            std::cout << "Engarrafamento." << std::endl;
        }
        insereNoRelogio(new Evento(sem_index, pista_index, des_index, tempo_evento, TROCA_DE_PISTA));

        for (int i = 0; i < relogio.size(); i++) {
            if (relogio.at(i)->getSemaforo() == sem_index && relogio.at(i)->getPista() == pista_index
                && relogio.at(i)->getTipo() == CHEGADA_AO_SEMAFORO) {
                insereNoRelogio(new Evento(sem_index, pista_index, -1, relogio.at(i)->getTempo() + 1, CHEGADA_AO_SEMAFORO));
                relogio.remove(relogio.at(i));
            }
        }
    }
}

void insereNoRelogio(Evento * evento) {
    if (relogio.size() == 0) {
        relogio.push_front(evento);
        return;
    }
    for (int i = 0; i < relogio.size(); i++) {
        if (evento->getTempo() < relogio.at(i)->getTempo() && (relogio.at(i)->getTempo() - evento->getTempo()) > 0) {
            relogio.insert(evento, i);
            return;
        }
    }
    relogio.push_back(evento);
}

void finalize() {
    std::cout << "Finalizando..." << std::endl;
    for (int i = 0; i < relogio.size(); i++) {
        delete relogio.pop_front();
    }
    for (int i = 0; i < pistas.size(); i++) {
        delete pistas.pop_front();
    }
    for (int i = 0; i < semaforos.size(); i++) {
        delete semaforos.pop_front();
    }
    std::cout << "Simulacao finalizada." << std::endl;

}
