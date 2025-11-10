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

    // Tamaño
    int size() const override {
        return n;
    }

    // Devuelve si está vacía
    bool empty() const override {
        return n == 0;
    }

    // Inserta en posición
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n)
            throw std::out_of_range("posición inválida");
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; i++)
                prev = prev->next;
            prev->next = new Node<T>(e, prev->next);
        }
        n++;
    }

    // Elimina en posición
    void erase(int pos) override {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("posición inválida");
        Node<T>* del;
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
        delete del;
        n--;
    }

    // Devuelve elemento
    T operator[](int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("posición inválida");
        Node<T>* cur = first;
        for (int i = 0; i < pos; i++)
            cur = cur->next;
        return cur->data;
    }

    // Imprime lista
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
