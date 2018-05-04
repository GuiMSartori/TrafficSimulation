#ifndef CARRO_H
#define CARRO_H

class Carro {
public:
    Carro(float tam);
    ~Carro();
    void setPosicao(float pos);
    float getPosicao();
    const float getPosicao() const;
    float getTamanho();
    const float getTamanho() const;
private:
    float tamanho;
    float posicao;
};

#endif /* CARRO_H */
