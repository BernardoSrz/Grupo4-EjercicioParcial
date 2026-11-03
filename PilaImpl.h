
#ifndef PILAIMPL_H
#define PILAIMPL_H

template <class T>
Nodo<T>::Nodo(T d) : dato(d), sig(nullptr) {}

template <class T>
Pila<T>::Pila() : tope(nullptr) {}

template <class T>
void Pila<T>::push(T dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    nuevo->sig = tope;
    tope = nuevo;
}

template <class T>
T Pila<T>::pop() {
    if (estaVacia()) return T();

    Nodo<T>* borrar = tope;
    T dato = borrar->dato;
    tope = borrar->sig;

    delete borrar;
    return dato;
}

template <class T>
T Pila<T>::top() {
    if (estaVacia()) return T();
    return tope->dato;
}

template <class T>
bool Pila<T>::estaVacia() {
    return tope == nullptr;
}

template <class T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        pop();
    }
}

#endif

