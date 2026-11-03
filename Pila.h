
#ifndef PILA_H
#define PILA_H

template <class T>
class Nodo {
public:
    T dato;
    Nodo<T>* sig;
    Nodo(T d);
};

template <class T>
class Pila {
private:
    Nodo<T>* tope;

public:
    Pila();
    void push(T dato);
    T pop();
    T top();
    bool estaVacia();

    Pila(const Pila<T>&) = delete;
    Pila<T>& operator=(const Pila<T>&) = delete;

    ~Pila();
};

#include "PilaImpl.h"

#endif
