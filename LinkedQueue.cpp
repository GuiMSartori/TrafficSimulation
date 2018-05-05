#include "LinkedQueue.h"
#include <cstdint>
#include <stdexcept>

template<typename T>
LinkedQueue<T>::LinkedQueue() {
    head = nullptr; //
    tail = nullptr;
    size_ = -1;
}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void LinkedQueue<T>::clear() {
    if (!empty()) {
        for (int i = 0; i < size(); i++) {
            dequeue();
        }
        size_ = -1;
    }
}

template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    Node *novo = new Node(data, nullptr);
    if (empty()) {
        tail = novo;
        head = novo;
    } else {
        tail->next(novo);
        tail = novo;
    }
    size_++;
}

template<typename T>
T LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("dequeue");
    }
    T retorno = head->data();
    Node *node_delete = head;
    head = head->next();
    delete node_delete;
    size_--;
    return retorno;
}

template<typename T>
T& LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("front");
    }
    return head->data(); //
}

template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("back");
    }
    return tail->data();
}

template<typename T>
bool LinkedQueue<T>::empty() const {
    return size_ == -1;
}

template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return size_ + 1;
}