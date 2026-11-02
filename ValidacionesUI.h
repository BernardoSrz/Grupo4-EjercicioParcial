#ifndef VALIDACIONESUI_H
#define VALIDACIONESUI_H

#include <string>
#include <cctype>
#include <cmath>
#include "Pila.h"

using namespace std;

string invertirCadena(string str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
    return str;
}

int obtenerPrioridad(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

string infijaAPostfija(string infija) {
    Pila<char> pilaOperadores;
    string postfija = "";

    for (size_t i = 0; i < infija.length(); i++) {
        char c = infija[i];
        if (isalnum(static_cast<unsigned char>(c))) {
            postfija += c;
        } else if (c == '(') {
            pilaOperadores.push(c);
        } else if (c == ')') {
            while (!pilaOperadores.estaVacia() && pilaOperadores.top() != '(') {
                postfija += pilaOperadores.pop();
            }
            if (!pilaOperadores.estaVacia()) pilaOperadores.pop();
        } else {
            while (!pilaOperadores.estaVacia() &&
                   pilaOperadores.top() != '(' &&
                   (obtenerPrioridad(pilaOperadores.top()) > obtenerPrioridad(c) ||
                   (obtenerPrioridad(pilaOperadores.top()) == obtenerPrioridad(c) && c != '^'))) {
                postfija += pilaOperadores.pop();
            }
            pilaOperadores.push(c);
        }
    }
    while (!pilaOperadores.estaVacia()) {
        postfija += pilaOperadores.pop();
    }
    return postfija;
}

string infijaAPrefija(string infija) {
    string invertida = invertirCadena(infija);
    for (size_t i = 0; i < invertida.length(); i++) {
        if (invertida[i] == '(') invertida[i] = ')';
        else if (invertida[i] == ')') invertida[i] = '(';
    }

    Pila<char> pilaOperadores;
    string prefijaTemp = "";

    for (size_t i = 0; i < invertida.length(); i++) {
        char c = invertida[i];
        if (isalnum(static_cast<unsigned char>(c))) {
            prefijaTemp += c;
        } else if (c == '(') {
            pilaOperadores.push(c);
        } else if (c == ')') {
            while (!pilaOperadores.estaVacia() && pilaOperadores.top() != '(') {
                prefijaTemp += pilaOperadores.pop();
            }
            if (!pilaOperadores.estaVacia()) pilaOperadores.pop();
        } else {
            while (!pilaOperadores.estaVacia() &&
                   pilaOperadores.top() != '(' &&
                   (obtenerPrioridad(pilaOperadores.top()) > obtenerPrioridad(c) ||
                   (obtenerPrioridad(pilaOperadores.top()) == obtenerPrioridad(c) && c == '^'))) {
                prefijaTemp += pilaOperadores.pop();
            }
            pilaOperadores.push(c);
        }
    }
    while (!pilaOperadores.estaVacia()) {
        prefijaTemp += pilaOperadores.pop();
    }
    return invertirCadena(prefijaTemp);
}

double evaluarPostfija(string postfija) {
    Pila<double> pilaValores;
    for (size_t i = 0; i < postfija.length(); i++) {
        char c = postfija[i];
        if (isdigit(static_cast<unsigned char>(c))) {
            pilaValores.push(c - '0');
        } else {
            if (pilaValores.estaVacia()) return 0;
            double val2 = pilaValores.pop();

            if (pilaValores.estaVacia()) return 0;
            double val1 = pilaValores.pop();

            if (c == '+') pilaValores.push(val1 + val2);
            else if (c == '-') pilaValores.push(val1 - val2);
            else if (c == '*') pilaValores.push(val1 * val2);
            else if (c == '/') {
                if (val2 == 0) return 0;
                pilaValores.push(val1 / val2);
            }
            else if (c == '%') {
                if (val2 == 0) return 0;
                pilaValores.push(fmod(val1, val2));
            }
            else if (c == '^') pilaValores.push(pow(val1, val2));
        }
    }
    if (pilaValores.estaVacia()) return 0;

    double resultado = pilaValores.pop();

    if (!pilaValores.estaVacia()) return 0;

    return resultado;
}

double evaluarPrefija(string prefija) {
    Pila<double> pilaValores;
    for (int i = (int)prefija.length() - 1; i >= 0; i--) {
        char c = prefija[i];
        if (isdigit(static_cast<unsigned char>(c))) {
            pilaValores.push(c - '0');
        } else {
            if (pilaValores.estaVacia()) return 0;
            double val1 = pilaValores.pop();

            if (pilaValores.estaVacia()) return 0;
            double val2 = pilaValores.pop();

            if (c == '+') pilaValores.push(val1 + val2);
            else if (c == '-') pilaValores.push(val1 - val2);
            else if (c == '*') pilaValores.push(val1 * val2);
            else if (c == '/') {
                if (val2 == 0) return 0;
                pilaValores.push(val1 / val2);
            }
            else if (c == '%') {
                if (val2 == 0) return 0;
                pilaValores.push(fmod(val1, val2));
            }
            else if (c == '^') pilaValores.push(pow(val1, val2));
        }
    }
    if (pilaValores.estaVacia()) return 0;

    double resultado = pilaValores.pop();

    if (!pilaValores.estaVacia()) return 0;

    return resultado;
}

#endif
