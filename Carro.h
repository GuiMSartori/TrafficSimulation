#ifndef CARRO_H
#define CARRO_H

class Carro {
public:
    Carro(double tam);

    double getTamanho();
    const double getTamanho() const;
private:
    double tamanho;
};

#endif /* CARRO_H */
