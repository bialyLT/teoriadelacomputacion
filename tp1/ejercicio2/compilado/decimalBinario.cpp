// hacer un codigo para pasar de decimal a binario y binario a decimal

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int decimalABinario(int n) {
    int binario = 0, base = 1;
    while (n > 0)
    {
        int ultimoDigito = n % 2;
        n /= 2;
        binario += ultimoDigito * base;
        base *= 10;
    }
    return binario;
}

int binarioADecimal(int n) {
    int decimal = 0, base = 1;
    while (n > 0)
    {
        int ultimoDigito = n % 10;
        n /= 10;
        decimal += ultimoDigito * base;
        base *= 2;
    }
    return decimal;
}

int main() {
    int opcion, numero;
    // la entrada va a ser un string
    
    
    cout << "Elige un tipo de conversion:\n1. Decimal a Binario\n2. Binario a Decimal\n";
    cin >> opcion;

    if (opcion == 1) {
        cout << "Ingresa un numero decimal: ";
        cin >> numero;
        cout << "Binario: " << decimalABinario(numero) << endl;
    } else if (opcion == 2) {
        cout << "Ingrese un numero binario: ";
        cin >> numero;
        cout << "Decimal: " << binarioADecimal(numero) << endl;
    } else {
        cout << "Opcion invalida!" << endl;
    }

    return 0;
}