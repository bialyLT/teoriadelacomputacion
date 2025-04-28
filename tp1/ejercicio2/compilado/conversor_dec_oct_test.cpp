// Conversor de Decimal ↔ Octal con prueba de rendimiento integrada.

#include <iostream>
#include <string>
#include <algorithm>   
#include <cctype>      
#include <vector>
#include <chrono>      
#include <iomanip>     

using namespace std;
using hr_clock = chrono::high_resolution_clock;


// ---- Conversor ----

// Convierte un entero decimal (con signo) a su representación en base 8 (octal).
// - n: valor decimal, puede ser negativo.
// - Devuelve: string con la representación octal incluyendo signo si es negativo.
string dec_a_oct(int n) {
    // Determinar signo
    string signo = (n < 0) ? "-" : "";
    // Trabajar con valor absoluto para extraer dígitos
    unsigned int valor = (n < 0) ? -n : n;
    if (valor == 0) 
        return "0";  // caso especial: 0

    string digitos;
    // Extraer dígitos en orden inverso
    while (valor > 0) {
        char d = char('0' + (valor % 8));  // resto → carácter '0'..'7'
        digitos += d;
        valor /= 8;
    }
    // Voltear la cadena para obtener el orden correcto
    reverse(digitos.begin(), digitos.end());
    return signo + digitos;
}

// Convierte una cadena en base 8 (octal), con posible signo, a un entero decimal.
// - s: string con dígitos octales y opcional signo '+' o '-'.
// - Devuelve: entero decimal equivalente.
// - Lanza invalid_argument en caso de formato inválido.
int oct_a_dec(const string& s) {
    if (s.empty()) 
        throw invalid_argument("Cadena vacia.");

    int signo = 1;
    size_t inicio = 0;
    // Procesar signo en la primera posición
    if (s[0] == '-') {
        signo = -1;
        inicio = 1;
    } else if (s[0] == '+') {
        inicio = 1;
    }
    if (inicio == s.size())
        throw invalid_argument("Cadena invalida (solo signo).");

    int resultado = 0;
    // Iterar sobre cada carácter y acumular el valor decimal
    for (size_t i = inicio; i < s.size(); ++i) {
        char c = s[i];
        if (c < '0' || c > '7')  // validar dígito octal
            throw invalid_argument("'" + s + "' no es representacion octal valida.");
        resultado = resultado * 8 + (c - '0');
    }
    return signo * resultado;
}


// ---- Modo interactivo ----

// Muestra un menú, lee la opción del usuario y realiza la conversión o prueba.
void modo_interactivo() {
    cout << "=== Conversor de Unidades (Decimal ↔ Octal) ===\n";
    cout << "1) Decimal a Octal\n";
    cout << "2) Octal a Decimal\n";
    cout << "3) Ejecutar prueba de rendimiento\n";
    cout << "Elija una opcion (1, 2, 3): ";

    string opcion;
    getline(cin, opcion);

    // Opción 3: invocar la prueba 
    if (opcion == "3") {
        extern void modo_benchmark();
        modo_benchmark();
        return;
    }

    // Validar opción 1 ó 2
    if (opcion != "1" && opcion != "2") {
    if (opcion != "1" && opcion != "2")
        return;
    }

    // Leer el número a convertir
    cout << "Ingrese el numero a convertir: ";
    string entrada;
    getline(cin, entrada);

    try {
        if (opcion == "1") {
            // Decimal → Octal
            int n = stoi(entrada);  // puede lanzar invalid_argument
            cout << n << " (decimal) es " 
                 << dec_a_oct(n) << " (octal)\n";
        } else {
            // Octal → Decimal
            cout << entrada << " (octal) es " 
                 << oct_a_dec(entrada) << " (decimal)\n";
        }
    } catch (const exception& e) {
        // Mostrar mensaje en caso de error de conversión o validación
        cout << "Error: " << e.what() << "\n";
    }
}


// ---- Modo benchmark ----

// Ejecuta la prueba de rendimiento sobre varias conversiones repetidas.
void modo_benchmark() {
    // Casos de prueba: valores típicos y extremos
    vector<int> test_numbers = {
        0, 1, 15, 16, 255, 1024, 65535, 1048576, 2147483647
    };
    const int repeats = 10'000;  // número de repeticiones

    // Lambdas que recorren todos los casos de prueba
    auto fn_dec_to_oct = [&]() {
        for (int n : test_numbers) 
            dec_a_oct(n);
    };
    auto fn_oct_to_dec = [&]() {
        for (int n : test_numbers) 
            oct_a_dec(dec_a_oct(n));
    };

    // Función de medición genérica usando high_resolution_clock
    auto medir = [&](auto&& func) {
        auto start = hr_clock::now();
        for (int i = 0; i < repeats; ++i) 
            func();
        auto end = hr_clock::now();
        chrono::duration<double> diff = end - start;
        return diff.count();  // segundos en double
    };

    // Medir tiempo total para cada función
    double time_do = medir(fn_dec_to_oct);  // decimal→octal
    double time_od = medir(fn_oct_to_dec);  // octal→decimal

    // Cálculos adicionales
    size_t total_calls = test_numbers.size() * repeats;
    double avg_do = time_do / total_calls;
    double avg_od = time_od / total_calls;

    // Imprimir resultados en formato tabular
    cout << left
         << setw(15) << "Implementacion"
         << setw(12) << "Funcion"
         << right << setw(15) << "Tiempo Total(s)"
         << setw(15) << "Llamadas"
         << setw(18) << "Promedio/Llamada(s)"
         << "\n";

    // Línea para Dec→Oct
    cout << left
         << setw(15) << "C++"
         << setw(12) << "Dec a Oct"
         << right << fixed << setprecision(6) << setw(15) << time_do
         << setw(15) << total_calls
         << setw(18) << scientific << setprecision(6) << avg_do
         << "\n";

    // Línea para Oct→Dec
    cout << left
         << setw(15) << "C++"
         << setw(12) << "Oct a Dec"
         << right << fixed << setprecision(6) << setw(15) << time_od
         << setw(15) << total_calls
         << setw(18) << scientific << setprecision(6) << avg_od
         << "\n";
}


int main() {
    // Siempre arrancamos mostrando el menú interactivo
    modo_interactivo();
    return 0;
}