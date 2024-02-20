#include <iostream>
#include <vector>
#include "adivinador.h"
using namespace std;

int main()
{
    int minimo = 1;
    int maximo = 1000;
    int tamano = 0;
    string entrada;
    cout << "Bienvenido! piense en un numero entero entre " << minimo << " y " << maximo << ", y hare lo posible por adivinarlo." << endl;
    while (tamano < 1 || tamano > maximo){
        cout << "Cuantos numeros quieres que de por intento? (entre 1 y " << maximo-minimo+1 << ")" << endl;
        getline(cin, entrada);
        tamano = stoi(entrada);
        if (tamano < 1)
            cout << "Debo darte al menos un numero!" << endl;
        if (tamano > maximo-minimo+1)
            cout << "No puedo darte tantos numeros!" << endl;
    }
    Adivinador *adivinador = new Adivinador(minimo, maximo, tamano);
    while (adivinador->obtenerNumero() < minimo){
        adivinador->adivinar();
        adivinador->preguntar();
        adivinador->analizar();
    }
    cout << "Asi que tu numero es " << adivinador->obtenerNumero() << "? Bien! lo he logrado!" << endl;
    delete adivinador;
    return 0;
}
