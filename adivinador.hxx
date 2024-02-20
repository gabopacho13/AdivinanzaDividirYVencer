#include "adivinador.h"
#include <random>
#include <chrono>
#include <sstream>
#include <regex>

using namespace std;

Adivinador::Adivinador(int minimo, int maximo, int tamano)
{
    this->minimo = minimo;
    this->maximo = maximo;
    this->numero = minimo-1;
    this->posibles.resize(tamano);
    this->respuestas.resize(tamano);
}

int Adivinador::obtenerNumero()
{
    return numero;
}

void Adivinador::adivinar()
{
    int totalPosibles = maximo-minimo+1;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    if (totalPosibles < posibles.size())
    {
        posibles.resize(totalPosibles);
        respuestas.resize(totalPosibles);
    }
    int tamanoRango = totalPosibles/posibles.size();
    adivinarAux(gen, tamanoRango, 0, posibles.size()-1);
}

void Adivinador::adivinarAux(mt19937 gen, int tamanoRango, int inicio, int fin)
{
    if (inicio > fin)
        return;
    else
    {
        int q = (inicio + fin)/2;
        int menorNum = tamanoRango*q+minimo;
        int mayorNum;
        if (q < posibles.size()-1)
            mayorNum = menorNum + (tamanoRango - 1);
        else
            mayorNum = maximo;
        uniform_int_distribution<> distribucion(menorNum, mayorNum);
        posibles[q] = distribucion(gen);
        adivinarAux(gen, tamanoRango, inicio, q-1);
        adivinarAux(gen, tamanoRango, q+1, fin);
    }
}

void Adivinador::preguntar()
{
    string linea;
    regex expresion("(<\\s*)*(=\\s*)?(>\\s*)*");
    int cont = 0;
    cout << "Alguno de estos es tu numero?: " << endl;
    for (int i = 0; i < posibles.size(); i++)
        cout << posibles[i] << " ";
    while (cont == 0)
    {
        bool valido = true;
        cout << "\nEscribe para cada numero si el numero mostrado es mayor (>), menor (<) o igual (=) a tu numero (puedes escribirlos seguidos o separados por espacios)" << endl;
        cin.ignore(0,'\n');
        getline(cin, linea);
        if(!regex_match(linea, expresion)){
            cout << "Algo no esta bien. Parece que la informacion ingresada no es congruente. Podrias responderme de nuevo?" << endl;
            continue;
        }
        istringstream ss(linea);
        char signo;
        while (ss >> signo)
        {
            respuestas[cont] = signo;
            if (respuestas[cont] == '>' && posibles[cont] == minimo){
                cout << "Algo no esta bien. El minimo que determinaste con tus respuestas no puede ser mayor a tu numero. Podrias responderme de nuevo?" << endl;
                cont = 0;
                valido = false;
                break;
            }
            if (respuestas[cont] == '<' && posibles[cont] == maximo){
                cout << "Algo no esta bien. El maximo que determinaste con tus respuestas no puede ser menor a tu numero. Podrias responderme de nuevo?" << endl;
                cont = 0;
                valido = false;
                break;
            }
            cont++;
        }
        if (!valido)
            continue;
        if (cont < posibles.size()){
            cout << "Algo no esta bien, faltan numeros por describir. Podrias responderme de nuevo?" << endl;
            cont = 0;
        }
        if (cont > posibles.size()){
            cout << "Algo no esta bien, hay mas comparaciones que numeros. Podrias responderme de nuevo?" << endl;
            cont = 0;
        }
    }
}

void Adivinador::analizar()
{
    analizarAux(0, posibles.size()-1);
}

void Adivinador::analizarAux(int inicio, int fin)
{
    if (inicio > fin)
        return;
    else
    {
        int q = (inicio + fin)/2;
        if (respuestas[q] == '=')
        {
            this->numero = posibles[q];
            return;
        }
        else if (respuestas[q] == '>')
        {
            this->maximo = posibles[q] - 1;
            analizarAux(inicio, q-1);
        }
        else if (respuestas[q] == '<')
        {
            this->minimo = posibles[q] + 1;
            analizarAux(q+1, fin);
        }
    }
}
