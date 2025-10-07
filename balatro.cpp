#include <iostream>
#include <cstdlib>
#include <ctime>

// Estructura de la carta
struct Carta {
    char Palo;      // 'C', 'E', 'D', 'T'
    int Categoria;  // 1-13 (A=1, J=11, Q=12, K=13)
    int Valor;      // 2-10: igual a Categoria, J/Q/K: 10, A: 11
    bool Jugada;    // true si ya fue jugada en la ronda
    Carta() {}
    Carta(char p, int c) : Palo(p), Categoria(c), Jugada(false) {
        if (c == 1) Valor = 11;
        else if (c >= 11 && c <= 13) Valor = 10;
        else Valor = c;
    }
};

// Nodo para lista enlazada
struct NodoCarta {
    Carta carta;
    NodoCarta* sig;
    NodoCarta(const Carta& c) : carta(c), sig(nullptr) {}
};

// Árbol binario de búsqueda para cada palo
struct NodoArbol {
    Carta carta;
    NodoArbol* izq;
    NodoArbol* der;
    NodoArbol(const Carta& c) : carta(c), izq(nullptr), der(nullptr) {}
};

// Inserción balanceada para crear el árbol de un palo
NodoArbol* crearArbolBalanceado(Carta cartas[], int ini, int fin) {
    if (ini > fin) return nullptr;
    int mid = (ini + fin) / 2;
    NodoArbol* nodo = new NodoArbol(cartas[mid]);
    nodo->izq = crearArbolBalanceado(cartas, ini, mid - 1);
    nodo->der = crearArbolBalanceado(cartas, mid + 1, fin);
    return nodo;
}

// Inicializa los 4 árboles, uno por palo
void inicializarArboles(NodoArbol* arboles[4]) {
    char palos[4] = {'C', 'E', 'D', 'T'};
    for (int i = 0; i < 4; ++i) {
        Carta cartas[13];
        for (int cat = 1; cat <= 13; ++cat)
            cartas[cat - 1] = Carta(palos[i], cat);
        arboles[i] = crearArbolBalanceado(cartas, 0, 12);
    }
}
