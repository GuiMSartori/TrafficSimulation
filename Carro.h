#ifndef CARRO_H
#define CARRO_H

class Carro {
public:
    Carro(float tam);

    float getTamanho();
    const float getTamanho() const;
private:
    float tamanho;
};

#endif /* CARRO_H */
