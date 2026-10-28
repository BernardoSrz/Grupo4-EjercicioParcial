#### **Ejercicio Parcial 1**

#### **Simulación del sistema de una calculadora mediante estructura de dato dinámica.**



*Integrantes: Ñacato Angie, Suárez Bernardo, Yánez José*

*Grupo: 4 - Pilas con notación infija, prefija y postfija.*



##### *1. Problema Real*



*Los procesadores y motores de cálculo como calculadoras o compiladores no evalúan expresiones matemáticas de forma lineal, debido a la ambigüedad de la jerarquía de operaciones y el uso de paréntesis. El problema real consiste en diseñar un "intermediario" que traduzca el lenguaje humano (notación infija) a un formato secuencial libre de ambigüedades (notaciones prefija y posfija) que una máquina pueda ejecutar eficientemente, haciendo uso de estructuras dinámicas temporales para gestionar la precedencia.*



##### *2. Objetivo*



*Diseñar e implementar en C++ el TDA Pila mediante clases genéricas y memoria dinámica, creando una UI en consola que permita visualizar cómo los operadores matemáticos ingresan y salen de la pila para convertir expresiones infijas a prefijas y posfijas, demostrando la asociatividad, precedencia y manejo seguro de la memoria.*



##### *3. Justificación de la Estructura (TDA Pila Genérica)*



*Se elige el TDA Pila (método LIFO - Last In, First Out) implementado con nodos dinámicos por las siguientes razones:*



* *El algoritmo de conversión (llamado Shunting Yard) requiere suspender la evaluación de operadores de baja precedencia hasta resolver los de alta precedencia. Una pila es la única estructura que permite apilar contextos (como abrir un paréntesis) y desapilarlos en orden inverso al cerrarlos.*
* *Al hacer la clase genérica (template <class T>), demostraremos reutilización. Usaremos una Pila<char> para almacenar los operadores matemáticos durante la conversión, y una Pila<string> auxiliar requerida para el algoritmo de conversión a prefija.*
* *La memoria dinámica con punteros asegura que no haya desbordamientos ni desperdicio de memoria, reservando nodos (new) solo cuando es necesario y liberándolos (delete) de inmediato al salir.*



##### *4. Operaciones Requeridas (TDA Manual)*



* *push(T dato): Reserva memoria dinámica para un nuevo nodo y lo enlaza como la nueva cima.*
* *pop(): Extrae el elemento de la cima, reconecta el puntero y libera la memoria para evitar memory leaks.*
* *top(): Devuelve el valor del tope sin eliminarlo.*
* *estaVacia(): Verifica si el puntero a la cima es nulo (caso límite).*



##### *5. Propuesta de UI y Librería Seleccionada*



* *Funciones nativas de consola de C++ mediante <iostream> y <windows.h>.*
* *No se utilizarán librerías gráficas pesadas como Qt o SFML. La UI utilizará coordenadas del cursor, borrado de pantalla y colores hexadecimales para renderizar dinámicamente un "contenedor ASCII" que mostrará visualmente el puntero a la cima, los nodos en memoria y los movimientos de apilado/desapilado en cada iteración del algoritmo.*
* *Compilación directa en el IDE Code::Blocks usando el compilador GCC estándar de Windows (MinGW). No requiere instalación de dependencias externas.*

