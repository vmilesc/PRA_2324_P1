#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <stdexcept>
#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    // Constructor
    ListLinked() {
        first = nullptr;
        n = 0;
    }

    // Destructor
    ~ListLinked() {
        Node<T>* aux;
        while (first != nullptr) {
            aux = first->next;
            delete first;
            first = aux;
        }
    }

    // Inserta al final
    void append(T e) override {
        insert(n, e);
    }

    // Inserta al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // Inserta en posición
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n)
            throw std::out_of_range("posición inválida");
        if (pos == 0)
            first = new Node<T>(e, first);
        else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; i++)
                prev = prev->next;
            prev->next = new Node<T>(e, prev->next);
        }
        n++;
    }

    // Elimina y devuelve elemento
    T remove(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("posición inválida");
        Node<T>* del;
        T elem;
        if (pos == 0) {
            del = first;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; i++)
                prev = prev->next;
            del = prev->next;
            prev->next = del->next;
        }
        elem = del->data;
        delete del;
        n--;
        return elem;
    }

    // Devuelve elemento
    T get(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("posición inválida");
        Node<T>* cur = first;
        for (int i = 0; i < pos; i++)
            cur = cur->next;
        return cur->data;
    }

    // Devuelve posición de un elemento
    int search(T e) override {
        Node<T>* cur = first;
        int i = 0;
        while (cur != nullptr) {
            if (cur->data == e)
                return i;
            cur = cur->next;
            i++;
        }
        return -1;
    }

    // Tamaño
    int size() override {
        return n;
    }

    // Vacía
    bool empty() override {
        return n == 0;
    }

    // Operador []
    T operator[](int pos) {
        return get(pos);
    }

    // Imprimir lista
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        Node<T>* cur = list.first;
        out << "[";
        while (cur != nullptr) {
            out << cur->data;
            if (cur->next != nullptr)
                out << ", ";
            cur = cur->next;
        }
        out << "]";
        return out;
    }
};

#endif
