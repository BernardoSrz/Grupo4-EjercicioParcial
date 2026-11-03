
#include <iostream>
#include <string>
#include <locale.h>
#include "Pila.h"
#include "ValidacionesUI.h"

using namespace std;

int main() {
setlocale(LC_ALL, "spanish");

    int opcion;
    string expresion;

    do {
        system("cls");
        cout << "--- PILAS: NOTACION INFIJA, PREFIJA Y POSTFIJA ---\n\n";
        cout << "1. Convertir a notación postfija\n";
        cout << "2. Convertir a notación prefija\n";
        cout << "3. Evaluar expresión postfija\n";
        cout << "4. Evaluar expresión prefija\n";
        cout << "5. Salir\n";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;

        if (opcion >= 1 && opcion <= 4) {
            cout << "\nIngrese la expresión: ";
            cin >> expresion;
        }

        switch (opcion) {
            case 1:
                {string respPost = infijaAPostfija(expresion);
                cout << "\n Expresión postfija: " << respPost << "\n" << endl;
                system("pause");
                break;}

            case 2:
                {string respPre = infijaAPrefija(expresion);
                cout << "\n Expresión prefija: " << respPre << "\n" << endl;
                system("pause");
                break;}

            case 3:
                {system("cls");
                double valorPost = evaluarPostfija(expresion);
                cout << "\n Resultado postfijo: " << valorPost << "\n" << endl;
                system("pause");
                break;}

            case 4:
                {system("cls");
                double valorPre = evaluarPrefija(expresion);
                cout << "\n Resultado prefijo: " << valorPre << "\n" << endl;
                system("pause");
                break;}

            case 5:
                cout << "\n Programa finalizado.\n";
                system("pause");
                break;

            default:
                cout << "\n Opción no valida.\n";
        }

    } while (opcion != 5);

    return 0;
}
