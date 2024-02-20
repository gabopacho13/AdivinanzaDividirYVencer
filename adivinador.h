#ifndef __ADIVINADOR_H__
#define __ADIVINADOR_H__

#include <vector>
#include <random>

using namespace std;

class Adivinador{
private:
    int numero;
    int maximo;
    int minimo;
    vector<int> posibles;
    vector<char> respuestas;
public:
    Adivinador(int minimo, int maximo, int tamano);
    int obtenerNumero();
    void adivinar();
    void adivinarAux(mt19937 gen, int tamanoRango, int inicio, int fin);
    void preguntar();
    void analizar();
    void analizarAux(int inicio, int fin);
};

#include "adivinador.hxx"
#endif // __ADIVINADOR_H__
