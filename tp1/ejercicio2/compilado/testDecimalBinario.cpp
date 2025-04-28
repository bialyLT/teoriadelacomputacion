#include <iostream>
#include <chrono> // Para medir el tiempo
#include <vector>

using namespace std;
using namespace chrono;

// Funciones originales
int decimalABinario(int n) {
    int binario = 0, base = 1;
    while (n > 0) {
        int ultimoDigito = n % 2;
        n /= 2;
        binario += ultimoDigito * base;
        base *= 10;
    }
    return binario;
}

int binarioADecimal(int n) {
    int decimal = 0, base = 1;
    while (n > 0) {
        int ultimoDigito = n % 10;
        n /= 10;
        decimal += ultimoDigito * base;
        base *= 2;
    }
    return decimal;
}

int main() {
    // Datos de prueba
    vector<int> numeros = {0, 1, 15, 16, 255, 1024, 65535, 1048576, 2147483647};
    int repeticiones = 10000; // Número de repeticiones
    
    // Variables para medir tiempo
    auto empezar = high_resolution_clock::now();
    
    // Medir decimalABinario
    for (int i = 0; i < repeticiones; ++i) {
        for (int n : numeros) {
            decimalABinario(n);
        }
    }
    
    auto terminar = high_resolution_clock::now();
    auto tiempo_dec_bin = duration_cast<nanoseconds>(terminar - empezar);

    // Ahora medir binarioADecimal
    empezar = high_resolution_clock::now();
    for (int i = 0; i < repeticiones; ++i) {
        for (int n : numeros) {
            int bin = decimalABinario(n); // Primero convertir a binario
            binarioADecimal(bin);         // Luego reconvertir a decimal
        }
    }
    
    terminar = high_resolution_clock::now();
    auto tiempo_bin_dec = duration_cast<nanoseconds>(terminar - empezar);
    
    // Cálculos
    int llamadas_totales = numeros.size() * repeticiones;
    double prom_dec_bin = tiempo_dec_bin.count() / (double)llamadas_totales;
    double prom_bin_dec = tiempo_bin_dec.count() / (double)llamadas_totales;
    
    // Mostrar resultados
    cout << "Resultados de rendimiento:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Funcion            | Tiempo Total (ms)    | Llamadas Totales | Tiempo Promedio (ns)" << endl;
    cout << "decimalABinario    | " << tiempo_dec_bin.count() / 1e6 << "             | " << llamadas_totales << "          | " << prom_dec_bin << endl;
    cout << "binarioADecimal    | " << tiempo_bin_dec.count() / 1e6 << "             | " << llamadas_totales << "          | " << prom_bin_dec << endl;
    cout << "----------------------------------------" << endl;


    cout << "Fin del programa." << endl;
    return 0;
}