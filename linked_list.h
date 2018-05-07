// Copyright [year] <Copyright Owner>

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

    template<typename T>
    class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void clear();
        void push_back(const T& data);
        void push_front(const T& data);
        void insert(const T& data, std::size_t index);
        void insert_sorted(const T& data);
        T& at(std::size_t index);
        T pop(std::size_t index);
        T pop_back();
        T pop_front();
        void remove(const T& data);
        bool empty() const;
        bool contains(const T& data) const;
        std::size_t find(const T& data) const;
        std::size_t size() const;

    private:

        class Node { // Elemento
        public:
            explicit Node(const T& data) :
            data_{data}
            {
            }

            explicit Node(const T& data, Node* next) :
            data_{data},
            next_{next}
            {
            }

            T& data() { // getter: dado
                return data_;
            }

            const T& data() const { // getter const: dado
                return data_;
            }

            Node* next() { // getter: próximo
                return next_;
            }

            const Node* next() const { // getter const: próximo
                return next_;
            }

            void next(Node* node) { // setter: próximo
                next_ = node;
            }

        private:
            T data_;
            Node* next_{nullptr};
        };

        Node* end() { // último nodo da lista
            auto it = head;
            for (auto i = 1u; i < size(); ++i) {
                it = it->next();
            }
            return it;
        }

        Node* head{nullptr};
        std::size_t size_{0u};
    };

} // namespace structures

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() { // constructor
}

template<typename T>
structures::LinkedList<T>::~LinkedList() { // destructor
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() { // clear
    Node *anterior, *proximo;
    proximo = head;
    for (int i = 0; i < size(); i++) {
        anterior = proximo;
        proximo = anterior->next();
        delete anterior;
    }
    size_ = 0;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) { // push_back
    insert(data, size_);
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) { // push_front
    Node *node = new Node(data, head);
    head = node;
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("insert");
    }
    if (index == 0) {
        push_front(data);
    } else {
        Node *novo, *anterior;
        anterior = head;
        for (unsigned int i = 0; i < index - 1; i++) {
            anterior = anterior->next();
        }
        novo = new Node(data, anterior->next());
        anterior->next(novo);
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) { // insert_sorted
    Node *node = head;
    if (size_ == 0) {
        push_front(data);
        return;
    }
    for (int i = 0; i < size_; i++, node = node->next()) {
        if (node->data() > data) {
            insert(data, i);
            return;
        }
    }
    push_back(data);
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) { // at
    if (index > size_) {
        throw std::out_of_range("at, index > size");
    }
    if (index < 0) {
        throw std::out_of_range("at, index < 0");
    }
    Node *node = head;
    for (int i = 0; i < index; i++) {
        node = node->next();
    }
    return node->data();
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) { // pop
    if (empty() || index < 0 || index > size_ - 1) {
        throw std::out_of_range("pop");
    }
    if (index == 0) {
        return pop_front();
    }
    Node *node, *node_delete;
    T retorno;
    node = head;
    for (int i = 0; i < index - 1; i++) {
        node = node->next();
    }
    node_delete = node->next();
    retorno = node_delete->data();
    node->next(node_delete->next());
    delete node_delete;
    size_--;
    return retorno;
}

template<typename T>
T structures::LinkedList<T>::pop_back() { // pop_back
    return pop(size_ - 1);
}

template<typename T>
T structures::LinkedList<T>::pop_front() { // pop_front
    if (empty()) {
        throw std::out_of_range("pop");
    }
    Node* node = head;
    T retorno = node->data();
    head = node->next();
    delete node;
    size_--;
    return retorno;
    ;
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) { // remove
    pop(find(data));
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const { // contains
    Node *node = head;
    for (int i = 0; i < size_; i++) {
        if (node == nullptr) {
            break;
        }
        if (node->data() == data) {
            return true;
        }
        node = node->next();
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const { // find
    Node *node = head;
    for (int i = 0; i < size_; i++) {
        if (node == nullptr) {
            break;
        }
        if (node->data() == data) {
            return i;
        }
        node = node->next();
    }
    return size();
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const { // size
    return size_;
}
