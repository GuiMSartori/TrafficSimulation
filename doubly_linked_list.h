// Copyright [year] <Copyright Owner>

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Lista Duplamente Encadeada
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    //! limpa lista
    void clear();
    //! insere no fim
    void push_back(const T& data);
    //! insere no início
    void push_front(const T& data);
    //! insere na posição
    void insert(const T& data, std::size_t index);
    //! insere em ordem
    void insert_sorted(const T& data);

    //! retira da posição
    T pop(std::size_t index);
    //! retira do fim
    T pop_back();
    //! retira do início
    T pop_front();
    //! retira específico
    void remove(const T& data);

    //! lista vazia
    bool empty() const;
    //! contém
    bool contains(const T& data) const;

    //! acesso a um elemento (checando limites)
    T& at(std::size_t index);
    //! getter constante a um elemento
    const T& at(std::size_t index) const;

    //! posição de um dado
    std::size_t find(const T& data) const;
    //! tamanho
    std::size_t size() const;

 private:
    class Node {public:
            explicit Node(const T& data):
                data_{data}	 	  	 	      	    	   	      	    	 	   	 	
            {}

            Node(const T& data, Node* next):
                data_{data},
                next_{next}
            {}

            Node(const T& data, Node* prev, Node* next):
                data_{data},
                prev_{prev},
                next_{next}
            {}

            T& data() {  // getter: dado
                return data_;
            }

            const T& data() const {  // getter-const: dado
                return data_;
            }

            Node* prev() {
                return prev_;
            }

            const Node* prev() const {
                return prev_;
            }

            void prev(Node* node) {
                prev_ = node;
            }

            Node* next() {
                return next_;
            }	 	  	 	      	    	   	      	    	 	   	 	

            const Node* next() const {
                return next_;
            }

            void next(Node* node) {
                next_= node;
            }private:
            T data_;
            Node* prev_;
            Node* next_;
    };

    Node* head;
    Node* tail;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {  // constructor
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {  // destructor
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {  // clear
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
void structures::DoublyLinkedList<T>::push_back(const T& data) {  // push_back
    Node *node = new Node(data, tail, nullptr);
    if (!size_ == 0) {
        tail->next(node);
    }
    tail = node;
    if (size_ == 0) {
        head = node;
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {  // push_front
    Node *node = new Node(data, head);
    if (!size_ == 0) {
        head->prev(node);
    }
    head = node;
    if (size_ == 0) {
        tail = node;
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {	 	  	 	      	    	   	      	    	 	   	 	
        throw std::out_of_range("insert");
    }
    if (index == 0) {
        push_front(data);
        return;
    }
    if (index == size_) {
        push_back(data);
        return;
    }
    if (index + 1 < size_/2) {
        Node *novo, *anterior;
        anterior = head;
        for (unsigned int i = 0; i < index - 1; i++) {
            anterior = anterior->next();
        }
        novo = new Node(data, anterior, anterior->next());
        anterior->next()->prev(novo);
        anterior->next(novo);
    } else {
        Node *novo, *proximo;
        proximo = tail;
        for (unsigned int i = 0; i < size_ - index - 1; i++) {
            proximo = proximo->prev();
        }
        novo = new Node(data, proximo->prev(), proximo);
        proximo->prev()->next(novo);
        proximo->prev(novo);
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
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
T structures::DoublyLinkedList<T>::pop(std::size_t index) {  // pop
    if (empty() || index < 0 || index > size_ - 1) {
        throw std::out_of_range("pop");
    }
    if (index == 0) {
        return pop_front();
    }
    if (index == size_ -1) {
        return pop_back();
    }

    Node *node_ref, *node_delete;
    T retorno;
    if (index + 1 < size_/2) {
        node_ref = head;
        for (int i = 0; i < index - 1; i++) {
            node_ref = node_ref->next();
        }
        node_delete = node_ref->next();
        retorno = node_delete->data();
        node_ref->next(node_delete->next());
        node_delete->next()->prev(node_ref);
    } else {	 	  	 	      	    	   	      	    	 	   	 	
        node_ref = tail;
        for (int i = 0; i < size_ - index - 2; i++) {
            node_ref = node_ref->prev();
        }
        node_delete = node_ref->prev();
        retorno = node_delete->data();
        node_ref->prev(node_delete->prev());
        node_delete->prev()->next(node_ref);
    }
    delete node_delete;
    size_--;
    return retorno;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {  // pop_back
    if (empty()) {
        throw std::out_of_range("pop_back");
    }
    Node* node = tail;
    T retorno = node->data();
    tail = node->prev();
    delete node;
    size_--;
    return retorno;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {  // pop_front
    if (empty()) {
        throw std::out_of_range("pop_front");
    }
    Node* node = head;
    T retorno = node->data();
    head = node->next();
    delete node;
    size_--;
    return retorno;;
}	 	  	 	      	    	   	      	    	 	   	 	

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {  // remove
    pop(find(data));
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {  // at
    if (index > size_ || index < 0) {
        throw std::out_of_range("at");
    }
    Node *node;
    if (index + 1 < size_/2) {
        node = head;
        for (int i = 0; i < index; i++) {
            node = node->next();
        }
    } else {
        node = tail;
        for (int i = 0; i < size_ - index - 1; i++) {
            node = node->prev();
        }
    }
    return node->data();
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {  // at
    if (index > size_ || index < 0) {
        throw std::out_of_range("at");
    }	 	  	 	      	    	   	      	    	 	   	 	
    Node *node;
    if (index + 1 < size_/2) {
        node = head;
        for (int i = 0; i < index; i++) {
            node = node->next();
        }
    } else {
        node = tail;
        for (int i = 0; i < size_ - index - 1; i++) {
            node = node->prev();
        }
    }
    return node->data();
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
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
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
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
std::size_t structures::DoublyLinkedList<T>::size() const {  // size
    return size_;
}
