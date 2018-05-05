#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <cstdint>

template<typename T>
//! Fila Encadeada
class LinkedQueue {
public:
    LinkedQueue();

    virtual ~LinkedQueue();

    //! limpar
    void clear();

    //! enfilerar
    void enqueue(const T& data);

    //! desenfilerar
    T dequeue();

    //! primeiro dado
    T& front() const;

    //! último dado
    T& back() const;

    //! fila vazia
    bool empty() const;

    //! tamanho
    std::size_t size() const;

private:

    class Node {
    public:
        explicit Node(const T& data) :
        data_{data}
        {
        }

        Node(const T& data, Node* next) :
        data_{data},
        next_{next}
        {
        }

        //! getter: info

        T& data() {
            return data_;
        }

        //! getter-constante: info

        const T& data() const {
            return data_;
        }

        //! getter: próximo

        Node* next() {
            return next_;
        }

        //! getter-constante: próximo

        const Node* next() const {
            return next_;
        }

        //! setter: próximo

        void next(Node* next) {
            next_ = next;
        }

    private:
        T data_;
        Node* next_;
    };

    Node* head; // nodo-cabeça
    Node* tail; // nodo-fim
    std::size_t size_; // tamanho
};

#endif /* LINKEDQUEUE_H */
