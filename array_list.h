// Copyright [year] <Copyright Owner>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

    template<typename T>
    //! aaa
    class ArrayList {
    public:
        ArrayList();
        //! aaa
        explicit ArrayList(std::size_t max_size);
        ~ArrayList();

        //! aaa
        void clear();
        //! aaa
        void push_back(T data);
        //! aaa
        void push_front(T data);
        //! aaa
        void insert(T data, std::size_t index);
        //! aaa
        void insert_sorted(T data);
        //! aaa
        T pop(std::size_t index);
        //! aaa
        T pop_back();
        //! aaa
        T pop_front();
        //! aaa
        void remove(T data);
        //! aaa
        bool full() const;
        //! aaa
        bool empty() const;
        //! aaa
        bool contains(const T& data) const;
        //! aaa
        std::size_t find(const T& data) const;
        //! aaa
        std::size_t size() const;
        //! aaa
        std::size_t max_size() const;
        //! aaa
        T& at(std::size_t index);
        //! aaa
        T& operator[](std::size_t index);
        //! aaa
        const T& at(std::size_t index) const;
        //! aaa
        const T& operator[](std::size_t index) const;

    private:
        T* contents;
        std::size_t size_;
        std::size_t max_size_;

        static const auto DEFAULT_MAX = 10u;
    };

} // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() { // construtor
    size_ = -1;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) { // construtor
    size_ = -1;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() { // destrutor
    delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() { // clear
    size_ = -1;
}

template<typename T>
void structures::ArrayList<T>::push_back(T data) { // push_back
    insert(data, size_ + 1);
}

template<typename T>
void structures::ArrayList<T>::push_front(T data) { // push_front
    insert(data, 0);
}

template<typename T>
void structures::ArrayList<T>::insert(T data, std::size_t index) { // insert
    if (full() || index < 0 || index > size_ + 1) {
        throw std::out_of_range("insert");
    }
    for (int i = size_ + 1; i > index; i--) {
        this->contents[i] = this->contents[i - 1];
    }
    this->contents[index] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(T data) { // insert_sorted
    if (empty()) {
        push_front(data);
    } else {
        for (int i = 0; i <= size_; i++) {
            if (data < contents[i]) {
                insert(data, i);
                return;
            }
        }
        push_back(data);
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) { // pop
    if (empty() || index < 0 || index > size_) {
        throw std::out_of_range("pop");
    }
    T retorno = contents[index];
    for (int i = index; i < size_; i++) {
        contents[i] = contents[i + 1];
    }
    size_--;
    return retorno;
}

template<typename T>
T structures::ArrayList<T>::pop_back() { // pop_back
    return pop(size_);
    ;
}

template<typename T>
T structures::ArrayList<T>::pop_front() { // pop_front
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(T data) { // remove
    pop(find(data));
}

template<typename T>
bool structures::ArrayList<T>::full() const { // full
    return size_ == max_size_ - 1;
}

template<typename T>
bool structures::ArrayList<T>::empty() const { // empty
    return size_ == -1;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const { // contains
    for (int i = 0; i < size(); i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const { // find
    for (int i = 0; i < size(); i++) {
        if (contents[i] == data) {
            return i;
        }
    }
    return size();
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const { // size
    return size_ + 1;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const { // max_size
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) { // at
    if (index > size_ || index < 0) {
        throw std::out_of_range("at");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) { // []
    if (index > size_ || index < 0) {
        throw std::out_of_range("[]");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const { // atc
    if (index > size_ || index < 0) {
        throw std::out_of_range("at const");
    }
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const { // [c
    if (index > size_ || index < 0) {
        throw std::out_of_range("[] const");
    }
    return contents[index];
}
