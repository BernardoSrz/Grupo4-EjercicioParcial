#ifndef VALIDACIONESUI_H
#define VALIDACIONESUI_H

#include <string>
#include <cctype>
#include <cmath>
#include <windows.h>
#include "Pila.h"
using namespace std;

void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void renderizarEstado(Pila<char>& pilaOriginal, string salida, char token, string tipoMensaje) {
    system("cls");
    
    color(11); // cyan
    cout << "=== SIMULACION SHUNTING YARD (" << tipoMensaje << ") ===\n\n";
    
    color(15); // blanco
    cout << " Token actual: [ ";
    color(14); // amarillo
    cout << token;
    color(15);
    cout << " ]\n\n";
    
    cout << " [ Pila de Operadores ]\n";
    
    Pila<char> pilaTemp; // pila auxiliar para dibujar

    if (pilaOriginal.estaVacia()) {
        cout << "    (vacia)\n";
    } else {
        while (!pilaOriginal.estaVacia()) { // vaciar la original para imprimir de arriba hacia abajo
            char op = pilaOriginal.pop();
            color(10); // verde para los operadores
            cout << "      |  " << op << "  |\n";
            pilaTemp.push(op); // guardar en la temporal
        }
    }
    
    color(15);
    cout << "      +-----+\n\n";
    
    while (!pilaTemp.estaVacia()) { // restaurar la pila original
        pilaOriginal.push(pilaTemp.pop());
    }
    
    cout << " Salida Temporal: ";
    color(14);
    cout << salida << "\n\n";
    color(15);
    Sleep(1000);
}

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
    renderizarEstado(pilaOperadores, postfija, ' ', "POSTFIJA");
    
    for (size_t i = 0; i < infija.length(); i++) {
        char c = infija[i];
        if (isalnum(static_cast<unsigned char>(c))) {
            postfija += c;
        } else if (c == '(') {
            pilaOperadores.push(c);
        } else if (c == ')') {
            while (!pilaOperadores.estaVacia() && pilaOperadores.top() != '(') {
                postfija += pilaOperadores.pop();
                renderizarEstado(pilaOperadores, postfija, c, "POSTFIJA");
            }
            if (!pilaOperadores.estaVacia()) pilaOperadores.pop();
        } else {
            while (!pilaOperadores.estaVacia() &&
                   pilaOperadores.top() != '(' &&
                   (obtenerPrioridad(pilaOperadores.top()) > obtenerPrioridad(c) ||
                   (obtenerPrioridad(pilaOperadores.top()) == obtenerPrioridad(c) && c != '^'))) {
                postfija += pilaOperadores.pop();
                renderizarEstado(pilaOperadores, postfija, c, "POSTFIJA");
            }
            pilaOperadores.push(c);
        }
        renderizarEstado(pilaOperadores, postfija, c, "POSTFIJA");
    }
    while (!pilaOperadores.estaVacia()) {
        postfija += pilaOperadores.pop();
        renderizarEstado(pilaOperadores, postfija, ' ', "POSTFIJA");
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
    renderizarEstado(pilaOperadores, prefijaTemp, ' ', "PREFIJA");

    for (size_t i = 0; i < invertida.length(); i++) {
        char c = invertida[i];
        if (isalnum(static_cast<unsigned char>(c))) {
            prefijaTemp += c;
        } else if (c == '(') {
            pilaOperadores.push(c);
        } else if (c == ')') {
            while (!pilaOperadores.estaVacia() && pilaOperadores.top() != '(') {
                prefijaTemp += pilaOperadores.pop();
                renderizarEstado(pilaOperadores, prefijaTemp, c, "PREFIJA");
            }
            if (!pilaOperadores.estaVacia()) pilaOperadores.pop();
        } else {
            while (!pilaOperadores.estaVacia() &&
                   pilaOperadores.top() != '(' &&
                   (obtenerPrioridad(pilaOperadores.top()) > obtenerPrioridad(c) ||
                   (obtenerPrioridad(pilaOperadores.top()) == obtenerPrioridad(c) && c == '^'))) {
                prefijaTemp += pilaOperadores.pop();
                renderizarEstado(pilaOperadores, prefijaTemp, c, "PREFIJA");
            }
            pilaOperadores.push(c);
        }
        renderizarEstado(pilaOperadores, prefijaTemp, c, "PREFIJA");
    }
    while (!pilaOperadores.estaVacia()) {
        prefijaTemp += pilaOperadores.pop();
        renderizarEstado(pilaOperadores, prefijaTemp, ' ', "PREFIJA");
    }
    
    string resultadoFinal = invertirCadena(prefijaTemp);
    system("cls");
    color(11);
    cout << "=== SIMULACION SHUNTING YARD (PREFIJA) ===\n\n";
    color(10);
    cout << " INVERSION FINAL COMPLETADA\n\n";
    color(15);
    cout << " Salida Prefija Real: ";
    color(14);
    cout << resultadoFinal << "\n\n";
    color(15);
    Sleep(1500);
    return resultadoFinal;
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
